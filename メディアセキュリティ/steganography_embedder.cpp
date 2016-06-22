#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

static const int Alphabet = 15;	//���ߍ��݂����A���t�@�x�b�g�ԍ�+1

int main(){
	cv::Mat temp = cv::imread("stego2.ppm", 0);		//�摜�̓ǂݍ���
	if (!temp.data) return -1;
	for (int i = 0; i < temp.rows; ++i){
		for (int j = 0; j < temp.cols; ++j){
			if (i == Alphabet && j == Alphabet) temp.at<unsigned char>(i, j) = 0;	//�s�E�񐔂��A���t�@�x�b�g�ԍ��̉�f�̒l��0��
			else if (temp.at<unsigned char>(i, j) < 250) temp.at<unsigned char>(i, j) += 2;	//����ȊO�͉�f�l�������グ�Ă����i���X�傫�����̂͂��̂܂܁j
		}
	}
	temp.at<unsigned char>(Alphabet - 1, Alphabet) = 0;	//��f�l��0�ɂ�����f�̎���̉�f��0�ɂ��Ă���
	temp.at<unsigned char>(Alphabet + 1, Alphabet) = 0;
	temp.at<unsigned char>(Alphabet, Alphabet - 1) = 0;
	temp.at<unsigned char>(Alphabet, Alphabet + 1) = 0;
	imshow("temp2", temp);

	cv::imwrite("test15.ppm", temp);	//���𖄂ߍ��񂾉摜�̕ۑ�
	cv::waitKey(0);
	return 0;
}
