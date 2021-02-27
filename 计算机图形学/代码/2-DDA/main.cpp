#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void init(void)
{
        glClearColor(1.0, 0.0, 1.0, 1.0);
        gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}
inline int round(const float a)
{
        return int(a + 0.5);
}
void setPixel(int x, int y)
{
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
}
void lineDDA(int x0, int y0, int xend, int yend)
{
        int dx = xend - x0, dy = yend - y0;
        int steps, k;
        float xIncrement, yIncrement, x = x0, y = y0;
        if(fabs(dx) > fabs(dy))
        {
                steps = fabs(dx);
        }
        else
        {
                steps = fabs(dy);
        }
        xIncrement = float(dx) / float(steps);
        yIncrement = float(dy) / float(steps);
        setPixel(round(x), round(y));
        for(k = 0; k < steps; k++)
        {
                x += xIncrement;
                y += yIncrement;
                setPixel(round(x), round(y));
        }
}

void display(void)
{
        glClear(GL_COLOR_BUFFER_BIT);   // 清空显示窗口
        glColor3f(0.0, 0.0, 0.0);       // 指定前景色
        glPointSize(3.0);               //点的大小
        glBegin(GL_POINTS);
                lineDDA(0, 200, 100, 300);
        glEnd();
        glFlush();
}
int main(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(400, 300);
        glutCreateWindow("MyTest");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
}
