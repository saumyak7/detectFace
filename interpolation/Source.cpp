
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/objdetect.hpp>
#include<vector>

using namespace cv;
using namespace std;

int main()
{
	// Load the Haar cascade file for face detection
	cv::CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");

	// Open the default video camera
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cout << "Failed to open the camera." << std::endl;
		return -1;
	}

	cv::namedWindow("Face Detection", cv::WINDOW_NORMAL);

	while (true)
	{
		cv::Mat frame;
		cap >> frame;  // Capture frame from camera

		// Convert frame to grayscale for face detection
		cv::Mat grayFrame;
		cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

		// Detect faces in the grayscale frame
		std::vector<cv::Rect> faces;
		faceCascade.detectMultiScale(grayFrame, faces, 1.1, 5, 0, cv::Size(30, 30));

		// Draw rectangles around the detected faces
		for (const cv::Rect& face : faces)
		{
			cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
		}

		// Display the resulting frame
		cv::imshow("Face Detection", frame);

		// Check for 'q' key press to exit
		if (cv::waitKey(1) == 'q')
			break;
	}

	// Release the video capture object and close the windows
	cap.release();
	cv::destroyAllWindows();

	return 0;
}
