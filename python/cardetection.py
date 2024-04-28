#import libraries
import cv2
import time
import math
import mediapipe as mp
from collections import defaultdict
from ultralytics import YOLO

# Define virtual line coordinates (replace with your desired location)
line_start_x = 200  # X-coordinate of line start point
line_start_y = 100  # Y-coordinate of line start point
line_end_x = 600  # X-coordinate of line end point
line_end_y = 100  # Y-coordinate of line end point

# Dictionary to store track history
track_history = defaultdict(lambda: [])

# Set to store unique track IDs that have crossed
crossed_track_ids = set()

# Variable to track total count of crossed objects (optional for display)
crossed_objects_count = 0
class_names = [
    'person', 'bicycle', 'car', 'motorbike', 'aeroplane', 'bus', 'train', 'truck', 'boat',
    'traffic light', 'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird', 'cat',
    'dog', 'horse', 'sheep', 'cow', 'elephant', 'bear', 'zebra', 'giraffe', 'backpack',
    'umbrella', 'handbag', 'tie', 'suitcase', 'frisbee', 'skis', 'snowboard', 'sports ball',
    'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard', 'tennis racket',
    'bottle', 'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple',
    'sandwich', 'orange', 'broccoli', 'carrot', 'hot dog', 'pizza', 'donut', 'cake', 'chair',
    'sofa', 'potted plant', 'bed', 'dining table', 'toilet', 'tvmonitor', 'laptop', 'mouse',
    'remote', 'keyboard', 'cell phone', 'microwave', 'oven', 'toaster', 'sink', 'refrigerator',
    'book', 'clock', 'vase', 'scissors', 'teddy bear', 'hair drier', 'toothbrush'
]


# loading gesture 
video = cv2.VideoCapture(0)

mpHands = mp.solutions.hands
hands = mpHands.Hands(max_num_hands = 1)
mpDraw = mp.solutions.drawing_utils

tipIds = [4, 8, 12, 16, 20]

success, img = video.read()


# function to detect number of fingers
def fingerCount(img):   
    success, img = video.read()
    img = cv2.flip(img, 1)

    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(img)

    lmList = []
    if results.multi_hand_landmarks:
        for handlms in results.multi_hand_landmarks:
            for id,lm in enumerate(handlms.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                lmList.append([id, cx, cy])
            mpDraw.draw_landmarks(img, handlms, mpHands.HAND_CONNECTIONS)

    fingers = []

    if(len(lmList)):
        if ((lmList[tipIds[0]][1] > lmList[tipIds[0] - 1][1] and lmList[tipIds[0]][2] <= lmList[tipIds[0] - 1][2]) or (lmList[tipIds[0]][1] < lmList[tipIds[0] - 1][1] and lmList[tipIds[0]][2] >= lmList[tipIds[0] - 1][2])):
            fingers.append(1)
        else:
            fingers.append(0)

        for id in range(1,5):
            if lmList[tipIds[id]][2] < lmList[tipIds[id] - 2][2]:
                fingers.append(1)
            else:
                fingers.append(0)

    totalFingers = sum(fingers) - 1

    return totalFingers, img


# function to detect the number of cars and draw boxes around
# with different colors and their speed
def detectCars(display):
    # loading vision
    model = YOLO('yolov8x.pt')

    # Open the video capture object
    cap = cv2.VideoCapture(r'C:\Users\AYAN ACHARYA\Downloads\carvideo.mp4')

    count = 0

    while cap.isOpened():
        count = 0

        success, frame = cap.read()

        if not success:
            break

        # Perform object detection and tracking (analyze entire video)
        results = model.track(frame, classes=[0, 2, 25, 67], persist=True, save=True, tracker="bytetrack.yaml")

        # Process detections to draw bounding boxes and count crossed objects
        for box, track_id, cls in zip(results[0].boxes.xywh.cpu(), results[0].boxes.id.int().cpu().tolist(), results[0].boxes.cls.int().cpu().tolist()):
            x, y, w, h = box

            track = track_history[track_id]
            track.append((float(x), float(y)))
            if len(track) > 30:
                track.pop(0)

            if class_names[cls] == 'car':
                count += 1

            # Check if object crossed the virtual line (first time only)
            if (track and len(track) > 1  # Ensure track history has at least 2 entries
                    and (track[0][0] < line_start_x and track[-1][0] > line_end_x)  # Check for crossing from left to right
                    and track_id not in crossed_track_ids):  # Avoid counting duplicates
                crossed_objects_count += 1
                crossed_track_ids.add(track_id)

            # Draw bounding box around detected object (example)
            cv2.rectangle(frame, (int(x - w/2), int(y - h/2)), (int(x + w/2), int(y + h/2)), (0, 255, 0), 4)
            class_name = class_names[cls]
            text_size, _ = cv2.getTextSize(class_name, cv2.FONT_HERSHEY_SIMPLEX, 3.0, 4)  # Experiment with larger font size
            text_x = int(x - w / 2) + 5  # Adjust X position to avoid overlapping with bounding box
            text_y = int(y - h / 2) - 15  # Increase negative offset to move text further above the box
            cv2.putText(frame, class_name, (text_x, text_y), cv2.FONT_HERSHEY_SIMPLEX, 3.0,(255, 255, 255) ,5)  # White text if background is dark

            # Function to check for dark background (replace with your implementation)
            # Optional: Display crossed object count on frame
            # cv2.putText(frame, f"Crossed Objects: {crossed_objects_count}", (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

        # Resize frame (optional)
        # Adjust resize factor based on your needs
        resized_frame = cv2.resize(frame, None, fx=0.75, fy=0.75)
        
        print('Display Value = ' + str(display))

        # Create window with desired size (optional)
        cv2.namedWindow('Object Detection and Tracking', cv2.WINDOW_NORMAL)
        cv2.resizeWindow('Object Detection and Tracking', 800, 600)  # Adjust window size as needed

        if display == 1:
            print('Car count = ' + str(count))

        # Display the frame with detections
        cv2.imshow('Object Detection and Tracking', frame)
        
        
            


# detecting number of fingers
# 1 finger prints the number of cars
# 2 fingers takes you to display video with boxes around the car

# sending text to serial port

numOfFings = 0

while True:
    numOfFings, img = fingerCount(img) 

    cv2.imshow('Fingers', img)
    
    print(numOfFings)
        
    if numOfFings > 0:
        detectCars(numOfFings)
        break
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

