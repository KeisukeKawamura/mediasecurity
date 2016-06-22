#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>

// �q�X�g�O�����f�[�^��\���p�̉摜�ɕϊ�
void make_histogram_image(cv::MatND& hist, cv::Mat& hist_img, int bin_num)
{
	// histogram��`�悷�邽�߂̉摜�̈���m��
	int img_width = 512;
	int img_height = 512;
	hist_img = cv::Mat(cv::Size(img_width, img_height), CV_8UC3);

	// �q�X�g�O�����̃X�P�[�����O
	// �q�X�g�O������bin�̒��ŁA�p�x���ő��bin�̍������A���傤�ǉ摜�̏c���Ɠ����l�ɂȂ�悤�ɂ���
	double max_val = 0.0;
	cv::minMaxLoc(hist, 0, &max_val);
	hist = hist * (max_val ? img_height / max_val : 0.0);

	// �q�X�g�O������bin�̐�������`������
	for (int j = 0; j < bin_num; ++j){
		// saturate_cast�́A���S�Ɍ^�ϊ����邽�߂̊֐��B�����ӂ��h�~
		int bin_w = cv::saturate_cast<int>((double)img_width / bin_num);
		cv::rectangle(
			hist_img,
			cv::Point(j*bin_w, hist_img.rows),
			cv::Point((j + 1)*bin_w, hist_img.rows - cv::saturate_cast<int>(hist.at<float>(j))),
			cv::Scalar::all(0), -1);
	}
}

int main()
{
	cv::Mat img = cv::imread("hsv1.png", CV_LOAD_IMAGE_GRAYSCALE);

	// �q�X�g�O�����𐶐����邽�߂ɕK�v�ȃf�[�^
	int image_num = 1;      // ���͉摜�̖���
	int channels[] = { 0 }; // cv::Mat�̉��Ԗڂ̃`���l�����g���� ����͔����摜�Ȃ̂�0�Ԗڂ̃`���l���ȊO�I�����Ȃ�
	cv::MatND hist;         // �����Ƀq�X�g�O�������o�͂����
	int dim_num = 1;        // �q�X�g�O�����̎�����
	int bin_num = 64;       // �q�X�g�O�����̃r���̐�
	int bin_nums[] = { bin_num };      // �����1�����̃q�X�g�O���������̂ŗv�f���͈��
	float range[] = { 0, 256 };        // �����f�[�^�̍ŏ��l�A�ő�l ����͋P�x�f�[�^�Ȃ̂Œl���[0, 255]
	const float *ranges[] = { range }; // �����1�����̃q�X�g�O���������̂ŗv�f���͈��

	// �����摜����P�x�̃q�X�g�O�����f�[�^(=�ebin���Ƃ̏o���񐔂��J�E���g��������)�𐶐�
	cv::calcHist(&img, image_num, channels, cv::Mat(), hist, dim_num, bin_nums, ranges);

	// �e�L�X�g�`���Ńq�X�g�O�����f�[�^���m�F
	std::cout << hist << std::endl;

	// �q�X�g�O�����f�[�^��\���p�̉摜�ɕϊ�
	// OpenCV�ł͊֐����p�ӂ���Ă��Ȃ��̂Ŏ��O�ŗp�ӂ���K�v������
	cv::Mat hist_img;
	make_histogram_image(hist, hist_img, bin_num);
	cv::imshow("histogram image", hist_img);

	cv::imwrite("hsv_histogram1.png", hist_img);

	// �摜�\���̂��߂�wait
	cv::waitKey(-1);

	return 0;
}