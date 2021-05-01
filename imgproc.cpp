#include "imgproc.h"

void edgeDetection(Mat inputImage, Mat& outputImage, int x, int y) {
	vector<int> vector(4);
	char robertsCrossOperator;
	for (size_t i = 1; i < inputImage.rows - 1; i++) {
		for (size_t j = x; j < y; j++) {
			if (inputImage.at<uchar>(i, j) != 0) {
				vector[0] = inputImage.at<uchar>(i + 1, j);
				vector[1] = inputImage.at<uchar>(i + 1, j + 1);
				vector[2] = inputImage.at<uchar>(i, j + 1);
				vector[3] = inputImage.at<uchar>(i, j);
				robertsCrossOperator = abs(vector[1] - vector[3]) + abs(vector[0] - vector[2]);
				outputImage.at<uchar>(i, j) = robertsCrossOperator;
			}
		}
	}
}

void resizeImage(Mat inputImage, Mat& outputImage, const float scale) {
	resize(inputImage, outputImage, cvSize(0, 0), scale, scale);
}
