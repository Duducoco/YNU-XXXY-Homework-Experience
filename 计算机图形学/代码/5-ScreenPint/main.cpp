#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PT = 6.2831853;
GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;
class screenPT
{
private:
        GLint x, y;
public:
        screenPT()
        {
                x = y = 0;
        }

        void setCoords(GLint xCood, GLint yCood)
        {
                x = xCood;
                y = yCood;
        }
        GLint getx() const
        {
                return x;
        }
        GLint gety() const
        {
                return y;
        }

};

static void init(void)
{
        screenPT hexVertex, circCtr;
        GLdouble theta;
        GLint k;
        circCtr.setCoords(winWidth / 2, winHeight / 2);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        regHex = glGenLists(1);
        glNewList(regHex, GL_COMPILE);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for(k = 0; k < 30; k++)
        {
                theta = TWO_PT * k / 30.0;
                hexVertex.setCoords(circCtr.getx() + 150 * cos(theta), circCtr.gety() + 150 * sin(theta));
                glVertex2i(hexVertex.getx(), hexVertex.gety());
        }
        glEnd();
        glEndList();
}
void regHexagon(void)
{
        glClear(GL_COLOR_BUFFER_BIT);
        glCallList(regHex);
        glFlush();
}
void winReshapeFcn(int newWidth, int newHeight)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, (GLdouble)newWidth, 0, (GLdouble)newHeight);
        glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(winWidth, winHeight);
        glutCreateWindow("Reshape_Function & Display_List Example");
        init();
        glutDisplayFunc(regHexagon);
        glutReshapeFunc(winReshapeFcn);
        glutMainLoop();
        return 0;
}




















