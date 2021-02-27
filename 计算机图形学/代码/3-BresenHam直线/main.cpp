#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void lineBresenHam(int x0, int y0, int xEnd, int yEnd) {
	int x, y;
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	//每次都从最左边的点画
	if(x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	} else {
		x = x0;
		y = y0;
	}
	float k = float(dy) / dx;       //斜率
	float d = 0;
	setPixel(x, y);
	if(fabs(dx) >= fabs(dy)) {       //斜率绝对值大于零小于1
		int steps = fabs(dx);
		for(int i = 0; i < steps; i++) {
			x++;
			d += k;
			if(k >= 0) {
				if(d > 1) {
					d = d - 1;
				}
				if(d > 0.5) {
					y++;
				}
			} else {
				if(d < -1) {
					d = d + 1;
				}
				if(d < -0.5) {
					y--;
				}
			}
			setPixel(x, y);
		}
	} else {
		int steps = fabs(dy);
		for(int i = 0; i < steps; i++) {
			d += 1 / k;
			if(k >= 0) {
				y++;
				if(d > 1) {
					d = d - 1;
				}
				if(d > 0.5) {
					x++;
				}
			} else {
				y--;
				if(d < -1) {
					d = d + 1;
				}
				if(d < -0.5) {
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
	glBegin(GL_POINTS);
	lineBresenHam(0, 100, 100, 300);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("MyTest");
	init();
	glutDisplayFunc(lineSegement);
	glutMainLoop();
	return 0;
}
