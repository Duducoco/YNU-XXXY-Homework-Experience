#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float s=1;
bool is_wl=true;
static GLuint texture;
float theta1,theta2,theta3; //转动角度
float alpha=0.8;//透明值
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};

GLubyte*  readImg(char* filename, int * imagewidth, int * imageheight)
{
    //打开文件
    int pixellength;
    GLubyte *  pixeldata ;
    FILE* pfile=fopen(filename,"rb");
    if(pfile == 0) exit(0);

    //读取图像大小
    fseek(pfile,0x0012,SEEK_SET);
    fread(imagewidth,sizeof(*imagewidth),1,pfile);
    fread(imageheight,sizeof(*imageheight),1,pfile);

    //计算像素数据长度
    pixellength=(*imagewidth)*3;
    while(pixellength%4 != 0)pixellength++;
    pixellength *= (*imageheight);

    //读取像素数据
    pixeldata = (GLubyte*)malloc(pixellength);
    if(pixeldata == 0) exit(0);

    fseek(pfile,54,SEEK_SET);
    fread(pixeldata,pixellength,1,pfile);

    fclose(pfile);
    return pixeldata;
}

void LoadTexture(char * filename, GLuint &texture)
{
    GLubyte * data;
    GLint width, height;

    //读文件
    data=readImg(filename, &width, &height );
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //线性滤图
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //自动生成纹理坐标，使用球面映射
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;

    //生参数1:GL_UNPACK_ALIGNMENT ，指定OpenGL如何从数据缓存区中解包图像数据
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    glEnable(GL_TEXTURE_2D);//打开纹理映射
    free(data); //释放纹理图像数据，纹理数据已由上一句生成并保存到纹理缓存中，使用完毕后应用glDeleteTextures释放纹理缓存
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);       //开启深度测试
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };  //漫反射系数，对应RGBA四个分量，A分量在混合开启后有效

    GLfloat mat_specular[] = { 0.8, 0.7, 0.8, 1.0 }; //镜面反射系数,对应RGBA四个分量，A分量在混合开启后有效
    GLfloat mat_shininess[] = { 50.0 };


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);//设置环境光系数和漫反射光系数
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //set material 镜面光反射
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//设置材料反射指数

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数

    glEnable(GL_BLEND);        //启用混合状态
    glEnable(GL_COLOR_MATERIAL);//材质跟踪当前绘图色
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //创建并绑定纹理
    LoadTexture("C:\\Users\\HP\\Desktop\\MyProject\\Graph\\TeaPot\\铜锈.bmp",texture);
}
void drawBoard()
{
    glColor4f(0.5,0.5,0.5,alpha);

    glBegin(GL_QUADS);
    glVertex3f(-0.5,-0.5,1);
    glVertex3f(-0.5,0.5,1);
    glVertex3f(0.5,0.5,1);
    glVertex3f(0.5,-0.5,1);
    glEnd();
}
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//最后一个参数为0，表示光源在无穷远处

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//光源位置

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);  //使用模型视图矩阵栈保存后面的几何变换
    glPushMatrix();              //保存世界坐标系到观察坐标系的变换矩阵

    glTranslatef(-0.8,0,0);
    glPushMatrix();

    glColor4f (1,1,1,1); //启用光源后，不在使用颜色函数对物体着色
    glBindTexture(GL_TEXTURE_2D, texture);
    glRotatef(theta1,1.0f,0.0f,0.0f);
    glRotatef(theta2,0.0f,1.0f,0.0f);
    glRotatef(theta3,0.0f,0.0f,1.0f);
    if(is_wl)
        glEnable(GL_TEXTURE_2D);//打开纹理
    else
    {
        glDisable(GL_TEXTURE_2D);//关闭纹理
        glColor3f(1,0,0);//设置红色
    }
    glutSolidTeapot(1*s);
    glPopMatrix();


    glPushMatrix();
    glDisable(GL_DEPTH_TEST); // 关闭深度测试
    glDisable(GL_TEXTURE_2D);//关闭纹理
    glTranslatef(1,0,2);

    drawBoard();//绘制透明薄板

    glEnable(GL_TEXTURE_2D);//打开纹理
    glEnable(GL_DEPTH_TEST);//打开深度测试
    glPopMatrix();

    glPopMatrix();                //恢复世界坐标系到观察坐标系的变换矩阵
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);  //使视区大小保持与窗口的显示区域大小一致
    glMatrixMode(GL_MODELVIEW);                    //使用模型视图矩阵栈
    glLoadIdentity();


    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);                 //使用投影矩阵栈，准备设定投影矩阵
    glLoadIdentity ();                            //初始化投影矩阵为单位矩阵

    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.5, 30.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
        if(alpha<1)
            alpha+=0.05;
        break;
    case '-':
        if(alpha>0)
            alpha-=0.05;
        break;
    case 'q':
    case 'Q':
        theta1+=5.0;
        break;
    case 'w':
    case 'W':
        theta1-=5.0;
        break;
    case 'a':
    case 'A':
        theta2+=5.0;
        break;
    case 's':
    case 'S':
        theta2-=5.0;
        break;
    case 'z':
    case 'Z':
        theta3+=5.0;
        break;
    case 'x':
    case 'X':
        theta3-=5.0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void myMouse(int button, int state, int x, int y) //滑轮控制缩放
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        is_wl = !is_wl;//左键显示\取消纹理
    }
    if(button== 3 ) //滑轮上滑放大
    {
        s+= 0.005;
    }
    if(button== 4) //滑轮下滑缩小
    {
        s-=0.005;
    }
    glutPostRedisplay(); //重新调用绘制函数
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}
