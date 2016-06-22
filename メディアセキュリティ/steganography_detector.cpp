#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

int main(){
	cv::Mat temp = cv::imread("test_yonten.ppm", 0);	//画像の読み込み
	if (!temp.data) return -1;

	cv::Mat temp2(temp.rows, temp.cols, CV_8U);
	cv::threshold(temp, temp2, 1, 255, cv::THRESH_BINARY);	//2値化処理（画素値が1以上のものは全て255に）
	for (int i = 0; i < 27; ++i){
		for (int j = 0; j < 27; ++j){
			if (temp2.at<unsigned char>(i, j) == 0) std::cout << "隠したメッセージは" << i - 1 << "番目のアルファベットです" << std::endl;
			//画素値が0の行数・列数の検出及び隠したメッセージの検出
		}
	}
	imshow("temp2", temp2);
	cv::imwrite("test_kensyutu.ppm", temp2);
//	cv::waitKey(0);
	return 0;
}