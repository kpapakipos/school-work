import tensorflow as tf
from tensorflow.keras import datasets, layers, models
from sklearn.metrics import confusion_matrix
import numpy as np

def __main__():
    fashion_mnist = datasets.fashion_mnist
    (train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

    train_images = train_images.reshape((60000, 28, 28, 1))
    test_images = test_images.reshape((10000, 28, 28, 1))

    # Normalize pixel values to be between 0 and 1
    train_images, test_images = train_images / 255.0, test_images / 255.0

    # Create the model and add all layers to it
    model = models.Sequential()
    model.add(layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1))) 
    model.add(layers.MaxPool2D())
    model.add(layers.Conv2D(64, (3, 3), activation='relu', input_shape=(28, 28, 1)))
    model.add(layers.MaxPool2D())
    model.add(layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)))
    model.add(layers.Flatten())
    model.add(layers.Dense(64, activation='relu'))
    model.add(layers.Dense(10, activation='softmax'))
    # Compile the model
    model.compile(loss='sparse_categorical_crossentropy', optimizer='sgd', metrics=['accuracy'])
    model.fit(x=train_images, y=train_labels, epochs=5) #5 epochs
    print('Problem 1:')

    # Accuracy rate
    # For some reason, calling model.evaluate causes the terminal to print out a huge progress bar, which  causes performance issues on my computer. verbose=0 fixes it.
    _test_loss, test_accuracy = model.evaluate(x=test_images, y=test_labels, verbose=0)
    print('Test accuracy:', test_accuracy)

    # Confusion matrix
    y_true = test_labels
    model_predict = model.predict(x=test_images)
    y_pred = []
    for pred in model_predict:
        y_pred.append(np.argmax(pred))
    print('Confusion matrix:')
    print(confusion_matrix(y_true, y_pred))


if __name__ == "__main__":
    __main__()