#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <exception>
#include <string>
#include <fstream>



int yonten_filter(cv::Mat image, int y, int x, int ch){
	cv::Vec3b pp = image.at<cv::Vec3b>(y, x);
	if (x< 0 || y<0 || x>(image.cols) - 2 || y>(image.rows) - 2){
		return 0;
	}
	else return pp(ch);
}



int main(){
	cv::Mat temp = cv::imread("stego_image.ppm", 1);
	if (!temp.data) return -1;

	cv::imshow("stego", temp);
	int intensity = temp.at<unsigned char>(4, 5); //X座標がx, Y座標がyに位置するピクセルの値を取得
	cv::Mat yonten(temp.rows, temp.cols, CV_8UC3);
	for (int j = 0; j < temp.rows; ++j){
		for (int i = 0; i < temp.cols; ++i){
			int xx[3];
			for (int ch = 0; ch < 3; ++ch){
				xx[ch] = (yonten_filter(temp, j, i, ch) + yonten_filter(temp, j - 1, i, ch) + yonten_filter(temp, j + 1, i, ch) + yonten_filter(temp, j, i - 1, ch) + yonten_filter(temp, j, i + 1, ch)) / 5;
			}
			yonten.at<cv::Vec3b>(j, i) = cv::Vec3b(xx[0], xx[1], xx[2]);
		}
	}

	std::cout << yonten.rows << "," << yonten.cols << std::endl;
	cv::imwrite("yonten.ppm", yonten);
	cv::imwrite("stego.ppm", temp);
	cv::imshow("yonten", yonten);
	//cv::waitKey(0);
}

/*
int main(){
cv::Mat_<unsigned char> temp = cv::imread("stego_image.ppm", -1);
if (!temp.data) return -1;

int intensity = temp.at<unsigned char>(4, 5); //X座標がx, Y座標がyに位置するピクセルの値を取得
std::cout << intensity << std::endl;
std::cout << temp.cols << std::endl;
cv::Mat_<unsigned char> yonten(temp.rows, temp.cols);
for (int i = 0; i < temp.rows; ++i){
for (int j = 0; j < temp.cols; ++j){
int xx = (yonten_filter(temp, i, j) + yonten_filter(temp, i - 1, j) + yonten_filter(temp, i + 1, j) + yonten_filter(temp, i, j - 1) + yonten_filter(temp, i, j + 1)) / 5;
yonten(i, j) = xx;
}
}
std::cout << yonten.rows << "," << yonten.cols << std::endl;
cv::imwrite("yonten.ppm", yonten);
//cv::imwrite("stego.ppm", temp);
cv::imshow("yonten", yonten);
//cv::waitKey(0);
}
*/

/*
unsigned char yonten_filter(cv::Mat image, int x, int y){

if (x< 0 || y<0 || x>(image.rows)-2 || y>(image.cols)-2){
return 0;
}
else return image.at<unsigned char>(x, y);
}
int main(){
cv::Mat temp = cv::imread("stego_image.ppm", -1);
if (!temp.data) return -1;
cv::imshow("stego", temp);
int intensity = temp.at<unsigned char>(4, 5); //X座標がx, Y座標がyに位置するピクセルの値を取得
cv::Vec3b p = temp.at<cv::Vec3b>(4, 5);
std::cout << intensity << std::endl;
std::cout << temp.rows << std::endl;
std::cout << temp.cols << std::endl;
int a = temp.rows;
int b = temp.cols;
cv::Mat yonten(a, b, CV_8UC3);
for (int i = 0; i < temp.rows; ++i){
for (int j = 0; j < temp.cols; ++j){
int xx = (yonten_filter(temp, i, j) + yonten_filter(temp, i - 1, j) + yonten_filter(temp, i + 1, j) + yonten_filter(temp, i, j - 1) + yonten_filter(temp, i, j + 1)) / 5;
yonten.at<unsigned char>(i, j) = xx;
}
}
std::cout << yonten.rows << "," << yonten.cols << std::endl;
cv::imwrite("yonten.ppm", yonten);
cv::imwrite("stego.ppm", temp);
cv::imshow("yonten", yonten);
//cv::waitKey(0);
}
*/