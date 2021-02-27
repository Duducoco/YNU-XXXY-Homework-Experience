#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-400, 400.0, -400, 400.0);
}

void DrawCirclePoint(int x0, int y0, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x+x0, y+y0);
	glEnd();
}
void CircleBresenHam(int x0, int y0, int R)
{
	float d = 1.25 - R;
	int x = 0;
	int y = R;
	DrawCirclePoint(x0,y0,x, y);	//坐标根据(x0,y0)平移
	for (int i = 0; i < sqrt(2)*R / 2; i++)
	{
		x++;
		if (d > 0)
		{
			y--;
			d += 2 * (x - y) + 5;
		}
		else
		{
			d += 2 * x + 3;
		}
		DrawCirclePoint(x0,y0,x, y);
		DrawCirclePoint(x0,y0,x, -y);
		DrawCirclePoint(x0, y0, -x, y);
		DrawCirclePoint(x0, y0, -x, -y);
		DrawCirclePoint(x0, y0, y, x);
		DrawCirclePoint(x0, y0, -y, x);
		DrawCirclePoint(x0, y0, y, -x);
		DrawCirclePoint(x0, y0, -y, -x);
	}
}
void CircleSegement(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   // 清空显示窗口
	glColor3f(1.0, 0.0, 0.0);       // 指定前景色
	glPointSize(3.0);               //点的大小
	CircleBresenHam(0, 100, 200); //画圆
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("MyCircle");
	init();
	glutDisplayFunc(CircleSegement);
	glutMainLoop();
	return 0;
}
