#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-400, 400.0, -400, 400.0);
}
int Myround(double x)
{
    return (int)(x+0.5);
}
void DrawCirclePoint(int x0, int y0, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x+x0, y+y0);
    glEnd();
}


void BresenhamOval(int xc, int yc, int a, int b)
{
    int sqa = a * a;
    int sqb = b * b;

    int x = 0;
    int y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    DrawCirclePoint(xc, yc, x, y);
    int P_x = Myround( (double)sqa/sqrt((double)(sqa+sqb)) );
    while(x <= P_x)
    {
        if(d < 0)
        {
            d += 2 * sqb * (2 * x + 3);
        }
        else
        {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        DrawCirclePoint(xc, yc, x, y);
        DrawCirclePoint(xc, yc, x, -y);
        DrawCirclePoint(xc, yc, -x, y);
        DrawCirclePoint(xc, yc, -x, -y);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while(y >= 0)
    {
        DrawCirclePoint(xc, yc, x, y);
        DrawCirclePoint(xc, yc, x, -y);
        DrawCirclePoint(xc, yc, -x, y);
        DrawCirclePoint(xc, yc, -x, -y);
        y--;
        if(d < 0)
        {
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
        {
            d = d - 2 * sqa * y - sqa;
        }
    }
}

void CircleSegement(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   // 清空显示窗口
    glColor3f(1.0, 0.0, 0.0);       // 指定前景色
    glPointSize(3.0);               //点的大小
    BresenhamOval(100, 100, 100,200); //画圆
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OvalCircle");
    init();
    glutDisplayFunc(CircleSegement);
    glutMainLoop();
    return 0;
}
