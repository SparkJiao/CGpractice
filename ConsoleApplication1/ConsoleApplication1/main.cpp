#include <gl/glut.h>  
#include <iostream>

using namespace std;

const int window_width = 800;
const int window_height = 600;
const int N = 500;

POINT first, second;
POINT start[N], endd[N];
int cnt = 0;
int flag = 1;

void drawLine(POINT fir, POINT sec) {
	glBegin(GL_LINES);
	glVertex2i(fir.x,fir.y);
	glVertex2i(sec.x, sec.y);
	glEnd();
}

void init() {
	cnt = 0;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1, 0, 0);
	glEnable(GL_COLOR_LOGIC_OP);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < cnt; i++)
		drawLine(start[i], endd[i]);
	glFlush();
}

void reshape(int width,int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, width, height);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flag) {
			flag ^= 1;
			first.x = x;
			first.y = window_height - y;
			second.x = x;
			second.y = window_height - y;
			drawLine(first, second);
			glLogicOp(GL_XOR);
		}else {
			drawLine(first, second);
			flag ^= 1;
			second.x = x;
			second.y = window_height - y;
			glLogicOp(GL_COPY);
			drawLine(first, second);
			start[cnt] = first;
			endd[cnt++] = second;
		}
	}
}

void move(int x, int y)
{
	if (!flag) {
		drawLine(first, second);
		second.x = x;
		second.y = window_height - y;
		drawLine(first, second);
		glFlush();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rubber");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(move);

	glutMainLoop();
}