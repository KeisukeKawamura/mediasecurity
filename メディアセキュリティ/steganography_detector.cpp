#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

int main(){
	cv::Mat temp = cv::imread("test_yonten.ppm", 0);	//�摜�̓ǂݍ���
	if (!temp.data) return -1;

	cv::Mat temp2(temp.rows, temp.cols, CV_8U);
	cv::threshold(temp, temp2, 1, 255, cv::THRESH_BINARY);	//2�l�������i��f�l��1�ȏ�̂��̂͑S��255�Ɂj
	for (int i = 0; i < 27; ++i){
		for (int j = 0; j < 27; ++j){
			if (temp2.at<unsigned char>(i, j) == 0) std::cout << "�B�������b�Z�[�W��" << i - 1 << "�Ԗڂ̃A���t�@�x�b�g�ł�" << std::endl;
			//��f�l��0�̍s���E�񐔂̌��o�y�щB�������b�Z�[�W�̌��o
		}
	}
	imshow("temp2", temp2);
	cv::imwrite("test_kensyutu.ppm", temp2);
//	cv::waitKey(0);
	return 0;
}