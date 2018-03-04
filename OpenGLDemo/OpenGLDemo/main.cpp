#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Angel.h"

const int NumPoints = 5000;
const int Ndivisions = 5;
const int Nvertices = 6e4;
typedef vec2 point2;
point2 points[Nvertices];

void triangle(point2 a, point2 b, point2 c) {
	static int i = 0;
	points[i++] = a;
	points[i++] = b;
	points[i++] = c;
}

void divide_triangle(point2 a, point2 b, point2 c, int k) {
	if (k) {
		//calculate the middle point of each edge of the current triangle
		point2 ab = (a + b) / 2.0;
		point2 ac = (a + c) / 2.0;
		point2 bc = (b + c) / 2.0;
		//generate the others triangles except the triangle at the center position
		divide_triangle(a, ab, ac, k - 1);
		divide_triangle(b, bc, ab, k - 1);
		divide_triangle(c, ac, bc, k - 1);
	} else {
		triangle(a, b, c);
	}
}


void init() {
	//vec2 points[NumPoints];
	//vec2 vertices[3] = { vec2(-1.0, -1.0),vec2(0.0, 1.0), vec2(1.0, -1.0) };

	//points[0] = vec2(0.25, 0.50);

	//for (int i = 1; i < NumPoints; ++i) {
		//int j = rand() % 3;
		//points[i] = (points[i - 1] + vertices[j]) / 2.0;
	//}

	point2 v[3] = { vec2(-1.0, -1.0),vec2(0.0, 1.0), vec2(1.0, -1.0) };
	divide_triangle(v[0], v[1], v[2], Ndivisions);

	GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
	glUseProgram(program);

	GLuint vao;
	std::cout << "stop here" << std::endl;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawArrays(GL_POINTS, 0, NumPoints);
	glDrawArrays(GL_TRIANGLES, 0, Nvertices);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 480);
	glutInitDisplayMode(GLUT_RGBA);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("sierpinski Gasket");

	glewExperimental = GL_TRUE;

	glewInit();

	init();

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}