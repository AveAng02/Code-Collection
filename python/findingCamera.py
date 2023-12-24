import cv2

# Try different camera indices until you find the correct one
for i in range(10):
    cap = cv2.VideoCapture(i)
    if cap.isOpened():
        print(f"Camera index {i} is available.")
        cap.release()
