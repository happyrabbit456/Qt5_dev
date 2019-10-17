#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	
	Mat image = imread("D:\\opencv-4.1.1\\opencv\\sources\\doc\\opencv.jpg");  // 读入图片
	imshow("OpenCV Logo", image);              // 在窗口中展示图片
	waitKey(0);                             // 等待键盘输入    
	
	return 0;
}