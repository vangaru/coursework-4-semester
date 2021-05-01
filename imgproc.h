#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <vector>

using namespace std;
using namespace cv;

void edgeDetection(Mat inputImage, Mat& outputImage, int x, int y);
void resizeImage(Mat inputImage, Mat& outputImage, const float scale);

