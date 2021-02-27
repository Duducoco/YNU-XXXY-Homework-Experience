#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>

GLsizei winWidth = 600, winHeight = 600;
GLuint regHex;//显示表标识
/*设置世界坐标范围*/
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt3D
{
public:
        GLfloat x, y, z;
};
typedef GLfloat Matrix4x4[4][4];
Matrix4x4 matComposite;

void init(void)
{
        glClearColor(1.0, 1.0, 1.0, 0.0);

}

void matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
        GLint row, col;
        for(row = 0; row < 4; row++)
        {
                for(col = 0; col < 4; col++)
                {
                        matIdent4x4[row][col] = (row == col);
                }
        }
}
void matrix4x4PreMultiply(Matrix4x4 m1, Matrix4x4 m2)
{
        GLint row, col;
        Matrix4x4 matTemp;
        for(row = 0; row < 4; row++)
        {
                for(col = 0; col < 4; col++)
                {
                        matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
                }
        }
        for(row = 0; row < 4; row++)
        {
                for(col = 0; col < 4; col++)
                {
                        m2[row][col] = matTemp[row][col];
                }
        }
}

void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
        Matrix4x4 matTransl3D;
        matrix4x4SetIdentity(matTransl3D);
        matTransl3D[0][3] = tx;
        matTransl3D[1][3] = ty;
        matTransl3D[2][3] = tz;
        matrix4x4PreMultiply(matTransl3D, matComposite);
}

void rotate3D(wcPt3D p1, wcPt3D p2, GLfloat radianAngle)
{
        Matrix4x4 matQuatRot;
        float axisVectLength = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
        float cosA = cos(radianAngle);
        float oneC = 1 - cosA;
        float sinA = sin(radianAngle);
        float ux = (p2.x - p1.x) / axisVectLength;
        float uy = (p2.y - p1.y) / axisVectLength;
        float uz = (p2.z - p1.z) / axisVectLength;
        translate3D(-p1.x, -p1.y, -p1.z);
        matrix4x4SetIdentity(matQuatRot);
        matQuatRot[0][0] = ux * ux * oneC + cosA;
        matQuatRot[0][1] = ux * uy * oneC - uz * sinA;
        matQuatRot[0][2] = ux * uz * oneC + uy * sinA;
        matQuatRot[1][0] = uy * ux * oneC + uz * sinA;
        matQuatRot[1][1] = uy * uy * oneC + cosA;
        matQuatRot[1][2] = uy * uz * oneC - ux * sinA;
        matQuatRot[2][0] = ux * uz * oneC - uy * sinA;
        matQuatRot[2][1] = uz * uy * oneC + ux * sinA;
        matQuatRot[2][2] = uz * uz * oneC + cosA;
        matrix4x4PreMultiply(matQuatRot, matComposite);
        translate3D(p1.x, p1.y, p1.z);
}

void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
        Matrix4x4 matScale3D;
        matrix4x4SetIdentity(matScale3D);
        matScale3D[0][0] = sx;
        matScale3D[0][3] = (1 - sx) * fixedPt.x;
        matScale3D[1][1] = sy;
        matScale3D[1][3] = (1 - sy) * fixedPt.y;
        matScale3D[2][2] = sz;
        matScale3D[2][3] = (1 - sz) * fixedPt.z;
        matrix4x4PreMultiply(matScale3D, matComposite);
}

void translate3d(GLint nverts, wcPt3D *verts)
{
        //对象顶点与复合变换矩阵的乘法，得到坐标变换后的点
        GLint k;
        for(k = 0; k < nverts; ++k)
        {
                verts[k].x = verts[k].x * matComposite[0][0] + verts[k].y * matComposite[0][1] + matComposite[0][2] * verts[k].z + matComposite[0][3];
                verts[k].y = verts[k].x * matComposite[1][0] + verts[k].y * matComposite[1][1] + matComposite[1][2] * verts[k].z + matComposite[1][3];
                verts[k].z = verts[k].x * matComposite[2][0] + verts[k].y * matComposite[2][1] + matComposite[2][2] * verts[k].z + matComposite[2][3];
        }
}
//void transformVerts3D()
//{
//    GLint k;
//    for (k = 0; k < nVerts; k++){
//        resultVerts[k].x = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2] * verts[k].z + matComposite[0][3];
//        resultVerts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2] * verts[k].z + matComposite[1][3];
//        resultVerts[k].z = matComposite[2][0] * verts[k].x + matComposite[2][0] * verts[k].y + matComposite[2][2] * verts[k].z + matComposite[2][3];
//    }
//}

void triangle(wcPt3D *verts)
{
        //输出一个空间三角形
        GLint k;
        glBegin(GL_TRIANGLES);
        for(k = 0; k < 3; ++k)
        {
                glVertex3f(verts[k].x, verts[k].y, verts[k].z);
        }
        glEnd();
}

void displayFcn()
{
        GLint nverts = 3;
        wcPt3D verts[3] = { { 20, 10.0, 0 }, { 100.0, 50.0, 50}, { 50.0, 50.0, 10 } }; //定义一个三角形
        GLdouble theta = 3.14159 / 4.0;//旋转45°
        wcPt3D p1, p2;
        p1.x = 0; p1.y = 0; p1.z = 0;
        p2.x = 1; p2.y = 1; p2.z = 1;//定义旋转轴为(0,0,1)
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 1.0);
        triangle(verts);//蓝色三角形为原始三角形
        matrix4x4SetIdentity(matComposite);

        rotate3D(p1, p2, theta); //旋转
        translate3d(nverts, verts);//对三角形坐标按照矩阵变换
        glColor3f(1.0, 0.0, 0.0);//红色为移动后的三角形
        triangle(verts);
        matrix4x4SetIdentity(matComposite);

        scale3D( 2, 2, 2 , p1);//缩放
        translate3d(nverts, verts);//对三角形坐标按照矩阵变换
        glColor3f(1.0, 1.0, 0.0);//红色为移动后的三角形
        triangle(verts);
        matrix4x4SetIdentity(matComposite);

        glFlush();
}

void winReshapeFcn(int newWidth, int newHeight) {
	//窗口重定形函数
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
	glOrtho(xwcMin, xwcMax, ywcMin, ywcMax,-55,0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(50, 50);
        glutInitWindowSize(600, 600);
        glutCreateWindow("Test");
        init();
        glutDisplayFunc(displayFcn);
        glutReshapeFunc(winReshapeFcn);
        glutMainLoop();
        return 0;
}


