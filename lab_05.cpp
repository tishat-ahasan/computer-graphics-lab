/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#include <stdlib.h>

using namespace std;
static int slices = 16;
static int stacks = 16;
float r,g,b;
int mx,my;
int X0,Y0,X1,Y1;
double theta;
int c;
int l=70;
int counter = 0;
bool check=true;
/* GLUT callback Handlers */


class Point{
public:
    double x;
    double y;
    double z;
    void set(double a,double b,double c){
        x=a;
        y=b;
        z=c;
    }
    
};

Point point[8];
Point on_screen[8];
Point local_origin;

Point Q_v;
double Q;
double q;
double dx,dy,dz;
double z_p;

double projection[4][4];

static void build_projection_matrix(){
    projection[0][0]=1;
    projection[0][1]=0;
    projection[0][2]=-(dx/dz);
    projection[0][3]=z_p*(dx/dz);

    projection[1][0]=0;
    projection[1][1]=1;
    projection[1][2]=-(dy/dz);
    projection[1][3]=z_p*(dy/dz);

    projection[2][0]=0;
    projection[2][1]=0;
    projection[2][2]=-(z_p/(q*dz));
    projection[2][3]=z_p*(1+(z_p/(q*dz)));
    
    projection[3][0]=0;
    projection[3][1]=0;
    projection[3][2]=-(1.0/(q*dz));
    projection[3][3]=(1+(z_p/(q*dz)));

}

static void project(double p[],double new_p[],int n){
    
    for(int i=0;i<n;i++){
        double sum=0;
        for(int j=0;j<n;j++){
            sum+=projection[i][j]*p[j];
        }
        new_p[i]=sum;
    }
    for(int i=0;i<n;i++){
        new_p[i]=new_p[i]/new_p[n-1];
    }
}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void drawPixel(int x,int y,int z)
{

    if(z==0)
    {
        // glColor3d(1,0,0);
        glVertex2i(x,y);
    }
    else if(z==1)
    {
        // glColor3d(0,1,0);
        glVertex2i(y,x);
    }
    else if(z==2)
    {
        // glColor3d(0,0,1);
        glVertex2i(-y,x);
    }
    else if(z==3)
    {
        // glColor3d(1,1,0);
        glVertex2i(-x,y);
    }
    else if(z==4)
    {
        // glColor3d(1,0,1);
        glVertex2i(-x,-y);
    }
    else if(z==5)
    {
        // glColor3d(0,1,1);
        glVertex2i(-y,-x);
    }
    else if(z==6)
    {
        // glColor3d(1,1,1);
        glVertex2i(y,-x);
    }
    else if(z==7)
    {
        // glColor3d(0.5,0.5,0.5);
        glVertex2i(x,-y);
    }
}
static void drawLine0(int x0,int y0,int x1,int y1,int z)
{
    int dy=y1-y0;
    int dx=x1-x0;
    int d = 2*dy - dx;
    int dE = 2*dy;
    int dNE = 2*(dy-dx);
    int x=x0;
    int y=y0;
    while(x<x1)
    {
        if(d<0)
        {
            d+=dE;
        }
        else
        {
            d+=dNE;
            y++;
        }
        x++;
        drawPixel(x,y,z);
    }
}

static int getZone(int dx,int dy)
{
    if((dx>=0)&&(dy>=0))
    {
        if(dx>=dy)
        {
            return 0;
        }
        return 1;
    }
    if((dx<0)&&(dy>=0))
    {
        if(abs(dx)>=dy)
        {
            return 3;
        }
        return 2;
    }
    if((dx<0)&&(dy<0))
    {
        if(abs(dx)>=abs(dy))
        {
            return 4;
        }
        return 5;
    }
    else
    {
        if(abs(dx)>=abs(dy))
        {
            return 7;
        }
        return 6;
    }
}
static void lineDraw(int x0,int y0,int x1,int y1)
{
    int dy=y1-y0;
    int dx=x1-x0;
    int z = getZone(dx,dy);


    if(z==0)
    {
        drawLine0(x0,y0,x1,y1,z);
    }
    else if(z==1)
    {
        drawLine0(y0,x0,y1,x1,z);
    }
    else if(z==2)
    {
        drawLine0(y0,-x0,y1,-x1,z);
    }
    else if(z==3)
    {
        drawLine0(-x0,y0,-x1,y1,z);
    }
    else if(z==4)
    {
        drawLine0(-x0,-y0,-x1,-y1,z);
    }
    else if(z==5)
    {
        drawLine0(-y0,-x0,-y1,-x1,z);
    }
    else if(z==6)
    {
        drawLine0(-y0,x0,-y1,x1,z);
    }
    else if(z==7)
    {
        drawLine0(x0,-y0,x1,-y1,z);
    }
}
static void display(void)
{
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    // glVertex2i(-320, 0);
    // glVertex2i(319, 0);
    // glVertex2i(0, -240);
    // glVertex2i(0, 239);
    glEnd();

    q = sqrt((Q_v.x * Q_v.x)+(Q_v.y * Q_v.y)+(Q_v.z * Q_v.z));
    dx=(Q_v.x)/q;
    dy=(Q_v.y)/q;
    dz=(Q_v.z)/q;

    build_projection_matrix();

    for(int i=0;i<8;i++){
        double p[4];
        double new_p[4];
        p[0]=point[i].x;
        p[1]=point[i].y;
        p[2]=point[i].z;
        p[3]=1;

        // if(c==0){
        //     printf("(%d,%d,%d)\n",(int)point[i].x,(int)point[i].y,(int)point[i].z);
        // }

        project(p,new_p,4);

        on_screen[i].x=new_p[0];
        on_screen[i].y=new_p[1];
        
        // if(c==0){
        //     printf("(%d,%d,%d)\n",(int)point[i].x,(int)point[i].y,(int)point[i].z);
        // }
    }
    c=1;
    glBegin(GL_POINTS);
    //glColor3d(0,0,1);
    for(int i=0;i<4;i++){
        int j=i+1;
        j=j%4;
        lineDraw(on_screen[i].x,on_screen[i].y,on_screen[j].x,on_screen[j].y);
    }
    //glColor3d(1,1,0);
    for(int i=4;i<8;i++){
        int j=i+1;
        if(j==8){
            j=4;
        }
        lineDraw(on_screen[i].x,on_screen[i].y,on_screen[j].x,on_screen[j].y);
    }
    //glColor3d(1,1,1);
    for(int i=0;i<4;i++){
        int j=i+4;
        
        lineDraw(on_screen[i].x,on_screen[i].y,on_screen[j].x,on_screen[j].y);
    }
    glEnd();
    glutSwapBuffers();
}


void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        check=true;

        mx = mousex-320;
        my = 240-mousey;

        //printf("x = %d , y = %d\n",mx,my);

        if(counter ==2 )
        {
            counter = 0;
        }
        if(counter == 0)
        {
            X0=mx;
            Y0=my;
            //printf("0 found\n");
            counter++;
        }
        else if(counter == 1)
        {
            X1=mx;
            Y1=my;

            counter++;

            int dy=Y1-Y0;
            int dx=X1-X0;
        }
        r=(rand()%9)/8;
        g=(rand()%9)/8;
        b=(rand()%9)/8;
    }

    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        check = false;
    }
    glutPostRedisplay();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */


int main(int argc, char *argv[])
{

    counter = 0;
    point[0].set(-l,l,l);
    point[1].set(-l,-l,l);
    point[2].set(l,-l,l);
    point[3].set(l,l,l);

    point[4].set(-l,l,-l);
    point[5].set(-l,-l,-l);
    point[6].set(l,-l,-l);
    point[7].set(l,l,-l);
    
    // for(int i=0;i<8;i++){
    //     printf("(%d,%d,%d)\n",(int)point[i].x,(int)point[i].y,(int)point[i].z);
    // }
    Q_v.set(-100.0,40.0,100.0);
    local_origin.set(0,0,0);
    z_p=100.0;
    theta = 1*(3.14159/180.0);
    c=0;

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
