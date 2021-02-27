#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class wcPt2D
{
    public :
        GLfloat x, y;
        wcPt2D(GLfloat x, GLfloat y);
        wcPt2D();

};

wcPt2D *p1 = new wcPt2D(0,0);
wcPt2D *p2 = new wcPt2D(400, 400);

wcPt2D *winMin = new wcPt2D(50, 50);
wcPt2D *winMax = new wcPt2D(200,200);

wcPt2D::wcPt2D( GLfloat tx, GLfloat ty )
{
    x = tx;
    y = ty;
}
wcPt2D::wcPt2D( )
{

}
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}
inline GLint round(const GLfloat a)
{
    return GLint(a+0.5);
}
const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

inline GLint inside(GLint code)
{
    return GLint (!code);
}
inline GLint reject(GLint code1, GLint code2)
{
    return GLint(code1 & code2);
}
inline GLint accept(GLint code1, GLint code2)
{
    return GLint (!(code1 | code2));
}

GLubyte encode( wcPt2D pt, wcPt2D winMin, wcPt2D winMax )
{
    GLubyte code = 0x00;
    if( pt.x < winMin.x )
        code = code | winLeftBitCode;
    if( pt.x > winMax.x )
        code  = code | winRightBitCode;
    if( pt.y < winMin.y )
        code = code | winBottomBitCode;
    if( pt.y > winMax.y )
        code = code | winTopBitCode;
    return code;
}

void swapPts( wcPt2D * p1, wcPt2D *p2 )
{
    wcPt2D tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void swapCodes(GLubyte *c1, GLubyte *c2)
{
    GLubyte tmp;
    tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

void lineClipCohSuth( /*wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2 */)
{
    GLubyte code1, code2;
    GLint done = false, plotLine = false;
    GLfloat m;
    while(!done)
    {
        code1 = encode(*p1, *winMin, *winMax);
        code2 = encode(*p2, *winMin, *winMax);
        if(accept(code1, code2))
        {
            done = true;
            plotLine = true;
        }
        else
        {
            if(reject(code1,code2))
                done = true;
            else
            {
                if(inside(code1))
                {
                    swapPts(p1, p2);
                    swapCodes(&code1, &code2);
                }
                if( p2->x != p1->x )
                    m = (p2->y - p1->y) / (p2->x - p1->x);
                if(code1 & winLeftBitCode)
                {
                    p1->y += (winMin->x - p1->x)*m;
                    p1->x  = winMin->x;
                }
                else
                {
                    if(code1 & winBottomBitCode)
                    {
                        if(p2->x != p1->x)
                            p1->x += (winMin->y - p1->y) / m;
                        p1->y = winMin->y;
                    }
                    else
                    {
                        if(code1 & winTopBitCode )
                        {
                            if(p2->x != p1->x)
                                p1->x += (winMax->y - p1->y) / m;
                            p1->y = winMax->y;
                        }
                    }
                }
            }
        }
    }
    if(plotLine)
    {
        glClear(GL_COLOR_BUFFER_BIT);   // 清空显示窗口
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2i(winMin->x, winMin->y);
            glVertex2i(winMax->x, winMin->y);

            glVertex2i(winMin->x, winMin->y);
            glVertex2i(winMin->x, winMax->y);

            glVertex2i(winMax->x, winMin->y);
            glVertex2i(winMax->x, winMax->y);

            glVertex2i(winMax->x, winMax->y);
            glVertex2i(winMin->x, winMax->y);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);       // 指定前景色
        glBegin(GL_LINES);
            glVertex2i(round(p1->x), round(p1->y));
            glVertex2i(round(p2->x), round(p2->y));
        glEnd();
        glFlush();
    }
}

int main(int argc, char ** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Split-Screen Example\n");
    init();

    glutDisplayFunc(lineClipCohSuth);

    glutMainLoop();
    return 0;
}


