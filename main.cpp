#include "imgproc.h"

#include <iostream>
#include <thread>
#include <ctime>

int main() {
	const size_t imageSizeInPixels = 5000;
	
	const string sourceImagePath = "deer.bmp";
	Mat sourceImage = imread(sourceImagePath, IMREAD_GRAYSCALE);
	
	const string edgeDetectedImagePathWT = "edge-detected-deer-wt.bmp";
	Mat edgeDetectedImageWT = sourceImage.clone();

	const string scaledImagePathWT = "scaled-deer-wt.bmp";
	Mat scaledImageWT;

	const float scale = 0.1;

	cout << endl << " ======== PROGRAM RUNNING WITH ONE THREAD ======== " << endl << endl;
	cout << " Image Size In Pixels : " << imageSizeInPixels << endl
		<< " Source Image Path : " << sourceImagePath << endl
		<< " Edge Detected Image Path : " << edgeDetectedImagePathWT << endl
		<< " Scale : " << scale << endl
		<< " Scaled Image Path : " << scaledImagePathWT << endl;

	clock_t clockStart = clock();

	edgeDetection(sourceImage, edgeDetectedImageWT, 1, 5000);
	resizeImage(sourceImage, scaledImageWT, scale);

	clock_t clockStop = clock();

	double time = static_cast<double>(clockStop - clockStart) / CLOCKS_PER_SEC;
	cout << " TIME: " << time << endl;

	imwrite(edgeDetectedImagePathWT, edgeDetectedImageWT);
	imwrite(scaledImagePathWT, scaledImageWT);

	const string edgeDetectedImagePathT = "edge-detected-deer-t.bmp";
	Mat edgeDetectedImageT = sourceImage.clone();

	const string scaledImagePathT = "scaled-deer-t.bmp";
	Mat scaledImageT;

	cout << endl << " ======== PROGRAM RUNNING WITH FIVE THREADS ======== " << endl << endl;
	cout << " Image Size In Pixels : " << imageSizeInPixels << endl
		<< " Source Image Path : " << sourceImagePath << endl
		<< " Edge Detected Image Path : " << edgeDetectedImagePathT << endl
		<< " Scale : " << scale << endl
		<< " Scaled Image Path : " << scaledImagePathT << endl;

	thread threads[6];

	threads[0] = thread(edgeDetection, sourceImage, ref(edgeDetectedImageT), 1, 1000);
	threads[1] = thread(edgeDetection, sourceImage, ref(edgeDetectedImageT), 1000, 2000);
	threads[2] = thread(edgeDetection, sourceImage, ref(edgeDetectedImageT), 2000, 3000);
	threads[3] = thread(edgeDetection, sourceImage, ref(edgeDetectedImageT), 3000, 4000);
	threads[4] = thread(edgeDetection, sourceImage, ref(edgeDetectedImageT), 4000, 5000);
	threads[5] = thread(resizeImage, sourceImage, ref(scaledImageT), scale);

	clockStart = clock();

	for (thread& thread : threads) {
		thread.join();
	}
	
	clockStop = clock();

	time = static_cast<double>(clockStop - clockStart) / CLOCKS_PER_SEC;

	cout << " TIME: " << time << endl;

	imwrite(edgeDetectedImagePathT, edgeDetectedImageT);
	imwrite(scaledImagePathT, scaledImageT);

	return 0;
}




