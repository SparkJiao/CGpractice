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
//xmlpath �ַ�����¼�Ǹ�.xml�ļ���·��
void detectAndDisplay(Mat image);
int main(int argc, char**argv)
{
	string path = "E:\\VSProjects\\����OpenCV��������⼰ʶ��\\ConsoleApplication1\\photos\\6.jpg";//�Լ��ͼƬ1.jpgΪ��
	Mat image = imread(path, -1);

	CascadeClassifier a;     //������������
	if (!a.load(xmlPath))     //�����ȡ�ļ���������������
	{
		cout << "�޷�����xml�ļ�" << endl;
		return 0;
	}
	//imshow("1", image);
	//waitKey(0);
	detectAndDisplay(image);// �������
	return 0;

}

void detectAndDisplay(Mat image)
{
	CascadeClassifier ccf;      //������������
	ccf.load(xmlPath);           //����opencv�Դ������ļ�
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

	imshow("1", image);
	imshow("2", image1);
	cvWaitKey(0);

}