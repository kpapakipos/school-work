import cv2
import numpy as np
from sklearn.decomposition import PCA
import matplotlib
matplotlib.get_cachedir()
import matplotlib.pyplot as plt

#1. Dimension reduction
#load images into array
#subjectImages is a 2D list
#subjectImages[0][1] is the first subject's second image
subjectImages = []
for i in range(0, 10):
    tmp = []
    for j in range(0, 10):
        tmp.append(cv2.imread('att_faces_10/s'+str(i+1)+'/'+str(j+1)+'.pgm', 0))
    subjectImages.append(tmp)
npSubjectImages = np.array(subjectImages)

#split images to training and testing
trainingImageNums = [1, 3, 4, 5, 7, 9]
testingImageNums = [2, 6, 8, 10]
trainingImages = []
testingImages = []

for subject in subjectImages:
    for trNum in trainingImageNums:
        tmp = []
        for row in subject[trNum-1]:
            for pixel in row:
                tmp.append(pixel)
        trainingImages.append(tmp)
    for teNum in testingImageNums:
        tmp = []
        for row in subject[teNum-1]:
            for pixel in row:
                tmp.append(pixel)
        testingImages.append(tmp)

npTrainingImages = np.array(trainingImages)
npTestingImages = np.array(testingImages)

#Prediction
kValues = [1, 2, 3, 6, 10, 20, 30, 50]
correctionRates = []
for k in kValues:
    #Calculate principal components- eigenfaces with all 60 training images
    pca = PCA(n_components=k).fit(trainingImages)
    projectedTraining = pca.transform(trainingImages)

    #correct is the number of correct guesses for this K-value
    correct = 0
    #image is a 10304-length list of pixel values
    for i, image in enumerate(testingImages):
        projectedTesting = pca.transform([image])

        diff = np.subtract(projectedTesting, projectedTraining)
        normalizedDiff = np.linalg.norm(diff, axis=1)

        diffMinIndex = np.argmin(normalizedDiff)

        predictedSubject = int((diffMinIndex) / 6)
        correctSubject = int((i) / 4)

        if predictedSubject == correctSubject:
            correct += 1
        
    correctionRates.append(correct / 40.0)
#plot diagram: correction_rate vs K_value
plt.plot(kValues, correctionRates)
plt.xlabel('K-Values')
plt.ylabel('Correction Rates')
plt.suptitle('Recognition Accuracy by K-Value')
plt.grid(True)
plt.legend(['Correction Rate vs K-Value'])
plt.show()