#include <iostream>
#include <opencv2/opencv.hpp>


void imageToDouble(cv::Mat inputImage, cv::Mat& outputImage) {
    double indexMax;
    inputImage.convertTo(outputImage, CV_32FC3, 1.0 / 255.0);
	
}


void colorChannelCompensation3C(cv::Mat &input, cv::Mat &doubleImage, cv::Mat &resultImage) {

    cv::Mat labChannelImage;
    cv::Mat grayscaleImage;
    cv::Mat mergedLAB;
    cv::Mat firstFilter;
    cv::Mat secondFilter;

	cv::cvtColor(input, grayscaleImage, cv::COLOR_BGR2GRAY);

	for(int r=0; r<input.rows; r++) {
		for(int c=0; c<input.cols; c++) {
            
			if(grayscaleImage.at<uchar>(r,c)<=216 ) {
				grayscaleImage.at<uchar>(r,c) = 1;
			}
			if(grayscaleImage.at<uchar>(r,c)>216 ) { 
				grayscaleImage.at<uchar>(r,c) = 0; 
			}
		}
 	}
     
	grayscaleImage.convertTo(grayscaleImage, CV_32FC3);
	cv::GaussianBlur(grayscaleImage, grayscaleImage, cv::Size(5,5), 5, 5);

    cv::cvtColor(doubleImage, labChannelImage, cv::COLOR_BGR2Lab);

	std::vector<cv::Mat> channelsLAB;
	cv::split(labChannelImage, channelsLAB);

	cv::GaussianBlur(channelsLAB[1],firstFilter,cv::Size(101,101), 101, 101);
	cv::GaussianBlur(channelsLAB[2],secondFilter,cv::Size(101,101), 101, 101);

	channelsLAB[1] = channelsLAB[1]- 1* firstFilter.mul(grayscaleImage);
	channelsLAB[2] = channelsLAB[2]- 1* secondFilter.mul(grayscaleImage);

	std::vector<cv::Mat> channelsToMerge;
	channelsToMerge.push_back(channelsLAB[0]);
	channelsToMerge.push_back(channelsLAB[1]);
	channelsToMerge.push_back(channelsLAB[2]);

	cv::merge(channelsToMerge,mergedLAB);
	cv::cvtColor(mergedLAB, resultImage, cv::COLOR_Lab2BGR);

}


int main(){

    cv::Mat image, doubleImage, resultImage;
    image = cv::imread("../inputs/cityscape_input.png");
    imageToDouble(image, doubleImage);

    colorChannelCompensation3C(image,doubleImage,resultImage);

    cv::imwrite("../results/resultCpp.png", resultImage*255);
    cv::imshow("Image",resultImage);
    cv::waitKey(0);
}