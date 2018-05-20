#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include <opencv2/gpu/gpu.hpp>

using namespace cv;
using namespace std;

string xmlPath = "E:\\VSProjects\\����OpenCV��������⼰ʶ��\\ConsoleApplication1\\haarcascade_frontalface_default.xml";

string HashValue(Mat &src)      //�õ�ͼƬ�Ĺ�ϣֵ
								//�ܾ�֮ǰд�ģ������벻������...ע�;��Ȳ�д��.....��Ǹ���������ǿ������е�
{
	string rst(64, '\0');
	Mat img;
	if (src.channels() == 3)
		cvtColor(src, img, CV_BGR2GRAY);
	else
		img = src.clone();
	resize(img, img, Size(8, 8));
	uchar *pData;
	for (int i = 0; i<img.rows; i++)
	{
		pData = img.ptr<uchar>(i);
		for (int j = 0; j<img.cols; j++)
		{
			pData[j] = pData[j] / 4;
		}
	}

	int average = mean(img).val[0];
	Mat mask = (img >= (uchar)average);
	int index = 0;
	for (int i = 0; i<mask.rows; i++)
	{
		pData = mask.ptr<uchar>(i);
		for (int j = 0; j<mask.cols; j++)
		{
			if (pData[j] == 0)
				rst[index++] = '0';
			else
				rst[index++] = '1';
		}
	}
	return rst;
}
int HanmingDistance(string &str1, string &str2)       //������ͼƬ�ĺ�������
{
	if ((str1.size() != 64) || (str2.size() != 64))
		return -1;
	int diff = 0;
	for (int i = 0; i<64; i++)
	{
		if (str1[i] != str2[i])
			diff++;
	}
	return diff;
}
void detectAndDisplay(Mat image)
{
	CascadeClassifier ccf;
	ccf.load(xmlPath);
	vector<Rect> faces;
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);
	ccf.detectMultiScale(gray, faces, 1.1, 3, 0, Size(50, 50), Size(500, 500));
	for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
	{
		rectangle(image, *iter, Scalar(0, 0, 255), 2, 8); //������������
	}
	Mat image1;
	for (size_t i = 0; i<faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		image1 = image(Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height));
	}
	//imshow("1", image);
	//imshow("2", image1);
	//cvWaitKey(0);
	image = image1;
}             //ʶ�𲢽�ȡ����
int main(int argc, char** argv)
{
	using std::cout;
	using std::endl;
	using std::cin;
	cout << "��������Ҫѡ���ͼƬ" << endl;
	int a, x, i;
	int diff[9];
	cin >> a;
	const string path1 = format("E:\\VSProjects\\����OpenCV��������⼰ʶ��\\ConsoleApplication1\\photos\\%d.jpg", a);
	Mat image1, image2;
	image1 = imread(path1, -1);
	string str1, str2, path2;
	cvNamedWindow("ѡ���ͼƬ", 1);
	/*cvResizeWindow("ѡ���ͼƬ",700,500);*/
	imshow("ѡ���ͼƬ", image1);
	detectAndDisplay(image1);
	str1 = HashValue(image1);
	//cvWaitKey(0);
	for (i = 1; i <= 4; i++)//��Ϊ����ɵľ���8��ͼƬ�ļ�⣬����ѭ��ֵΪ8
	{
		path2 = format("E:\\VSProjects\\����OpenCV��������⼰ʶ��\\ConsoleApplication1\\photos\\%d.jpg", i);
		image2 = imread(path2, -1);
		detectAndDisplay(image2);
		str2 = HashValue(image2);
		diff[i] = HanmingDistance(str1, str2);
	}

	int min = 10000000, t = -1;
	for (i = 1; i <= 4; i++)    //ѭ��ֵΪ8������ԭͼƬ����������С������ͼƬ
	{
		if (min>diff[i] && diff[i] != 0)
		{
			min = diff[i];
			t = i;
		}           //�����ı��Ϊt
	}
	if (t == -1) {
		cout << "error" << endl;
		cin >> t;
		return 0;
	}
	path2 = format("E:\\VSProjects\\����OpenCV��������⼰ʶ��\\ConsoleApplication1\\photos\\%d.jpg", t);
	image2 = imread(path2, -1);//��ͼƬt��ʾ����
	cvNamedWindow("���Ƶ�ͼƬ", 1);
	imshow("���Ƶ�ͼƬ", image2);//��ʱ��ʾ�ľ��������Ƶ���Ƭ
	cvWaitKey(0);
	//cin.get();                    //�Ե��س���
	cout << "t=" << t << endl;
	int tmp;
	cin >> tmp;
}