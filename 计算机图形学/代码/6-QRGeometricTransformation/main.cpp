#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-400, 400.0, -400, 400.0);
}

void translationTransformation(int *x, int * y, int xSpan, int ySpan)//平移变换
{
	int transformat[3][3] = { 1, 0, 0,
							  0, 1, 0,
							  xSpan, ySpan, 1
	};
	int xEnd = *x, yEnd = *y;
	int Location[1][3] = {xEnd, yEnd, 1};
	int nextLocation[1][3] = { 0 };
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				nextLocation[i][j] += Location[i][k] * transformat[k][j];
			}
		}
	}
	*x = nextLocation[0][0] * nextLocation[0][2];
	*y = nextLocation[0][1]*nextLocation[0][2];
}

void scaleTransformation(int *x, int * y, float xScale, float yScale)//比例变换
{
	float transformat[3][3] = { xScale, 0, 0,
							  0, yScale, 0,
							  0, 0, 1 };
	float Location[1][3] = { *x, *y, 1 };
	float nextLocation[1][3] = { 0 };
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				nextLocation[i][j] += Location[i][k] * transformat[k][j];
			}
		}
	}
	*x = nextLocation[0][0] * nextLocation[0][2];
	*y = nextLocation[0][1] * nextLocation[0][2];
}

void rotateTransformation(int *x, int * y, float theta)//旋转变换
{
	float transformat[3][3] = { cos(theta), sin(theta), 0,
							  -sin(theta), cos(theta), 0,
							  0, 0, 1 };
	float Location[1][3] = { *x, *y, 1 };
	float nextLocation[1][3] = { 0 };
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				nextLocation[i][j] += Location[i][k] * transformat[k][j];
			}
		}
	}
	*x = nextLocation[0][0] * nextLocation[0][2];
	*y = nextLocation[0][1] * nextLocation[0][2];
}
void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
//		rotateTransformation(&x, &y, 0);
//		scaleTransformation(&x, &y, 0.5);
		translationTransformation(&x, &y, -200,-200);
		glVertex2i(x, y);
	glEnd();
}


void lineBresenHam(int x0, int y0, int xEnd, int yEnd) {
	int x, y;
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	//每次都从最左边的点画
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}
	float k = float(dy) / dx;       //斜率
	float d = 0;
	setPixel(x, y);
	if (fabs(dx) >= fabs(dy)) {       //斜率绝对值大于零小于1
		int steps = fabs(dx);
		for (int i = 0; i < steps; i++) {
			x++;
			d += k;
			if (k >= 0) {
				if (d > 1) {
					d = d - 1;
				}
				if (d > 0.5) {
					y++;
				}
			}
			else {
				if (d < -1) {
					d = d + 1;
				}
				if (d < -0.5) {
					y--;
				}
			}
			setPixel(x, y);
		}
	}
	else {
		int steps = fabs(dy);
		for (int i = 0; i < steps; i++) {
			d += 1 / k;
			if (k >= 0) {
				y++;
				if (d > 1) {
					d = d - 1;
				}
				if (d > 0.5) {
					x++;
				}
			}
			else {
				y--;
				if (d < -1) {
					d = d + 1;
				}
				if (d < -0.5) {
					x++;
				}
			}
			setPixel(x, y);
		}
	}
}
void lineSegement(void) {
	glClear(GL_COLOR_BUFFER_BIT);   // 清空显示窗口
	glColor3f(1.0, 0.0, 0.0);       // 指定前景色
	glPointSize(3.0);               //点的大小
	lineBresenHam(0, 0, 400, 400);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("changeFormat");
	init();
	glutDisplayFunc(lineSegement);
	glutMainLoop();
	return 0;
}
