#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
int main()
{
	//ͼƬ������ӵ�����Ŀ¼��
	Mat srcImage = imread("lulu_12.jpg");
	//��ʾԭͼ
	imshow("��ʾԭͼ", srcImage);
	//���и�ʴ����
// 	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
// 	Mat dstImage;
// 	erode(srcImage, dstImage, element);
// 
// 	//���о�������
// 	Mat BlurImage;
// 	blur(srcImage, BlurImage, Size(7, 7));
// 	imshow("������ʾ", BlurImage);
// 	//��ʾЧ��ͼ
// 	imshow("Ч��ͼ", dstImage);

	Mat edge, grayImage;
	//��ԭͼתת�Ҷ�ͼ��
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	blur(grayImage, edge, Size(3, 3));
	Canny(edge, edge, 3, 9, 3);
	imshow("Ч��ͼ", edge);

	
	waitKey(0);
	return 0;
}