#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

static const int Alphabet = 12;	//���ߍ��݂����A���t�@�x�b�g�ԍ�+1

int main(){
	cv::Mat temp = cv::imread("test_kensyutu.ppm", 0);		//�摜�̓ǂݍ���
	if (!temp.data) return -1;

	cv::imwrite("test_kensyutu.jpg", temp);	//���𖄂ߍ��񂾉摜�̕ۑ�
}