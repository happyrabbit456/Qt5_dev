#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	
	Mat image = imread("D:\\opencv-4.1.1\\opencv\\sources\\doc\\opencv.jpg");  // ����ͼƬ
	imshow("OpenCV Logo", image);              // �ڴ�����չʾͼƬ
	waitKey(0);                             // �ȴ���������    
	
	return 0;
}