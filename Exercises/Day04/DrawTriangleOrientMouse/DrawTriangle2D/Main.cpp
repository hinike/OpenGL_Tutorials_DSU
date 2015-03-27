#define _USE_MATH_DEFINES
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
 
using namespace std;

int WIDTH = 500;
int HEIGHT = 500;

float initAngle = 0;

void DrawGraph() {
	glBegin(GL_LINES);

	//draw Minor grid lines
	glColor3f(0.75, 0.75, 0.75);

	for (int i = 0; i <= WIDTH; i += 5) {
		if (i % 50 == 0)
			continue; 
		glVertex2i(i, 0);	glVertex2i(i, HEIGHT); 
	}

	for (int i = 0; i <= HEIGHT; i += 5) {
		if (i % 50 == 0)
			continue; 

		glVertex2i(0, i);	glVertex2i(WIDTH, i);
	}

	//major grid lines
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i <= WIDTH; i += 50) {
		glVertex2i(i, 0);	glVertex2i(i, HEIGHT);
	}
	for (int i = 0; i <= HEIGHT; i += 50) {
		glVertex2i(0, i);	glVertex2i(WIDTH, i);
	}
	glEnd();
}
  
void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	WIDTH = nw;
	HEIGHT = nh;
	glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawCircle(int x0, int y0, int radius, int numSegments = 3, float initAngle=M_PI/2.0f) {
	
	float dTheta = (2*M_PI) / numSegments;
	float theta = initAngle;
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1);
		for (int i = 0; i < numSegments; ++i) {
			int x_prime = x0 + radius * cos(theta);
			int y_prime = y0 + radius * sin(theta);
			theta += dTheta;
			glVertex2i(x_prime, y_prime);
		}
	glEnd();

	//we output a point to show the apex
	theta = initAngle;
	int x_prime = x0 + radius * cos(theta);
	int y_prime = y0 + radius * sin(theta);
	glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex2i(x_prime, y_prime);
	glEnd();
}

void OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT); 
	DrawGraph(); 
	
	DrawCircle(WIDTH >> 1, HEIGHT >> 1, 100, 3, initAngle);

	glutSwapBuffers();
}
void OnInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH); 
}
 
void OnMouseMove(int x, int y) {
	x = x - (WIDTH >> 1);
	y = (HEIGHT >> 1) - y;
	initAngle = atan2(y, x);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Drawing Simple 2D Mouse Location Oriented Triangle");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize); 
	glutPassiveMotionFunc(OnMouseMove); 
	OnInit();

	glutMainLoop();
	return 0;
}