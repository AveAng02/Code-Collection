import numpy as np
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.datasets import mnist
from tensorflow.keras.utils import to_categorical
from PIL import Image

def predict_new_digit(model, image_path):
    
    img = Image.open(image_path).convert('L') 

    img = img.resize((28, 28))  
    
    img_array = np.array(img) / 255.0

    img_array = np.expand_dims(img_array, axis=0)  

    prediction = model.predict(img_array)

    digit_class = np.argmax(prediction)

    return digit_class

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

train_images, test_images = train_images / 255.0, test_images / 255.0

train_labels = to_categorical(train_labels)

test_labels = to_categorical(test_labels)

model = models.Sequential()

model.add(layers.Flatten(input_shape=(28, 28))) 

model.add(layers.Dense(128, activation='relu'))

model.add(layers.Dropout(0.2))

model.add(layers.Dense(10, activation='softmax'))  

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

model.fit(train_images, train_labels, epochs=5, validation_data=(test_images, test_labels))

test_loss, test_acc = model.evaluate(test_images, test_labels)

print(f'Test accuracy: {test_acc}')

image_path = 'testImage.jpg'

predicted_digit = predict_new_digit(model, image_path)

print(f'The predicted digit is: {predicted_digit}')
