#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

unsigned char yonten_filter(cv::Mat image, int x, int y){	//指定画素の値を返す関数
	if (x< 0 || y<0 || x>(image.rows) - 2 || y>(image.cols) - 2) return 0;
	else return image.at<unsigned char>(x, y);
}


int main(){
	cv::Mat temp = cv::imread("test15.ppm", 0);	//画像の読み込み
	if (!temp.data) return -1;
	cv::imshow("stego", temp);
	int intensity = temp.at<unsigned char>(4, 5); //X座標がx, Y座標がyに位置する画素の値を取得
	cv::Mat yonten(temp.rows, temp.cols, CV_8U);
	for (int i = 0; i < temp.rows; ++i){
		for (int j = 0; j < temp.cols; ++j){
			int xx = (yonten_filter(temp, i, j) + yonten_filter(temp, i - 1, j) + yonten_filter(temp, i + 1, j) + yonten_filter(temp, i, j - 1) + yonten_filter(temp, i, j + 1)) / 5;	//4点移動平均フィルタの計算
			yonten.at<unsigned char>(i, j) = xx;
		}
	}
	cv::imwrite("test_yonten15.ppm", yonten);	//フィルタをかけた画像を保存
//	cv::waitKey(0);
	return 0;
}
