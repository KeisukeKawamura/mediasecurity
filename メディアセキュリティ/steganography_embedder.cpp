#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

static const int Alphabet = 15;	//埋め込みたいアルファベット番号+1

int main(){
	cv::Mat temp = cv::imread("stego2.ppm", 0);		//画像の読み込み
	if (!temp.data) return -1;
	for (int i = 0; i < temp.rows; ++i){
		for (int j = 0; j < temp.cols; ++j){
			if (i == Alphabet && j == Alphabet) temp.at<unsigned char>(i, j) = 0;	//行・列数がアルファベット番号の画素の値を0に
			else if (temp.at<unsigned char>(i, j) < 250) temp.at<unsigned char>(i, j) += 2;	//それ以外は画素値を少し上げておく（元々大きいものはそのまま）
		}
	}
	temp.at<unsigned char>(Alphabet - 1, Alphabet) = 0;	//画素値を0にした画素の周りの画素も0にしておく
	temp.at<unsigned char>(Alphabet + 1, Alphabet) = 0;
	temp.at<unsigned char>(Alphabet, Alphabet - 1) = 0;
	temp.at<unsigned char>(Alphabet, Alphabet + 1) = 0;
	imshow("temp2", temp);

	cv::imwrite("test15.ppm", temp);	//情報を埋め込んだ画像の保存
	cv::waitKey(0);
	return 0;
}
