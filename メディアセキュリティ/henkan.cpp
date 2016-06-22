#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

static const int Alphabet = 12;	//埋め込みたいアルファベット番号+1

int main(){
	cv::Mat temp = cv::imread("test_kensyutu.ppm", 0);		//画像の読み込み
	if (!temp.data) return -1;

	cv::imwrite("test_kensyutu.jpg", temp);	//情報を埋め込んだ画像の保存
}