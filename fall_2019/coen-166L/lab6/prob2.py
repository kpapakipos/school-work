import tensorflow as tf
from tensorflow.keras import datasets, layers, models
from sklearn.metrics import confusion_matrix
import numpy as np
import math
import matplotlib.pyplot as plt
from tensorflow.keras import losses

def __main__():
    fashion_mnist = datasets.fashion_mnist
    (train_images, _train_labels), (test_images, _test_labels) = fashion_mnist.load_data()

    train_images = train_images.reshape((60000, 28, 28, 1))
    test_images = test_images.reshape((10000, 28, 28, 1))

    # Normalize pixel values to be between 0 and 1
    train_images, test_images = train_images / 255.0, test_images / 255.0

    shownImages = []
    for img in test_images[0:10]:
        shownImages.append(img)

    # Create and add all layers to the model
    for P in [10, 50, 200]:
        model = models.Sequential()
        model.add(layers.Flatten())
        model.add(layers.Dense(P))
        model.add(layers.Dense(28*28*2, activation='relu'))
        model.add(layers.Dense(28*28))
        model.add(layers.Reshape((28, 28)))
        # Compile the model
        model.compile(optimizer='adam', loss=losses.mean_squared_error)
        model.fit(x=train_images, y=train_images, batch_size=64, epochs=10) #10 epochs

        # Do analysis and print output
        print('Problem 2:')
        # For some reason, calling model.evaluate causes the terminal to print out a huge progress bar, which causes performance issues on my computer. verbose=0 fixes this.
        mse = model.evaluate(x=test_images, y=test_images, verbose=0)
        print(mse)
        psnr = 10*math.log10(1/mse)
        print(psnr)
        print('for P value {}, PSNR = {}'.format(P, psnr))
        # Build up the decompressed images to be shown
        predictions = model.predict(x=test_images)
        for img in predictions[0:10]:
            shownImages.append(img)

    # Show images
    plt.figure(figsize=(10,5))
    plt.gray()
    for i in range(40):
        plt.subplot(4,10,i+1)
        plt.xticks([])
        plt.yticks([])
        plt.grid(False)
        plt.imshow(np.squeeze(shownImages[i]))
    plt.show()

if __name__ == "__main__":
    __main__()