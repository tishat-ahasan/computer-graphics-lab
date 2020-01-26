#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 640
#define HEIGHT 480
#define RAD 40




int flag=0,flag2=0;
int p=0;
int x00=0,x11=0,y00=0,y11=0;
int ax0[1000],ax1[1000],ay0[1000],ay1[1000];
int k=0;



int type;

bool isCollide(){

    int d = (x00-x11)*(x00-x11);
    d += (y00-y11)*(y00-y11);

    int radious = 4*RAD*RAD;
    if (d > radious) return false;
    return true;
}

void drawline0(int x0,int y0,int x1,int y1){
    glColor3d(1,0,0);
    int dx = x1-x0;
    int dy = y1-y0;
    
    int d = 2*dy-dx;
    if (type == 1){
        if(d<0){
            x00++;
        }
        else{
            x00++;
            y00--;
        }
    }
    else{
        if(d<0){
            x11++;
        }
        else{
            x11++;
            y11--;
        }
    }
}

void drawline1(int x0,int y0,int x1,int y1){
    glColor3d(0,1,0);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = dx-2*dy;
    if (type == 1){
        if(d<0){
            x00++;
            y00++;
            }
        else{
            y00++;            
        }
    }
    else{
        if(d<0){
            x11++;
            y11++;
            }
        else{
            y11++;            
        }
    }
}

void drawline2(int x0,int y0,int x1,int y1){
    glColor3d(0,0,1);
    int dx = x1-x0;
    int dy = y1-y0;
    
    int d = -dy-2*dx;
        if (type == 1){
        if(d>0){
            x00--;
            y00++;}
        else{
            y00++;}
    }
    else{
        if(d>0){
            x11--;
            y11++;}
        else{
            y11++;}
    }
}


void drawline3(int x0,int y0,int x1,int y1){
    glColor3d(1,1,0);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = -2*dy-dx;
    if (type==1){
        if(d<0){
            x00--;
            y00++;}
        else{
            x00--;}
        }
    else{
        if(d<0){
            x11--;
            y11++;}
        else{
            x11--;}
    }
}

void drawline4(int x0,int y0,int x1,int y1){
    glColor3d(1,0,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = -2*dy+dx;
    if (type == 1){
        if(d<0){  //dW
            x00--;
        }
        else{       //dSW
            x00--;
            y00--;
        }
    }
    else{

        if(d<0){  //dW
            x11--;
        }
        else{       //dSW
            x11--;
            y11--;
        }
    }
}


void drawline5(int x0,int y0,int x1,int y1){
    glColor3d(1,1,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = -dy+2*dx;
    if(type == 1){
        if(d>0){    //S
            y00--;
        }
        else{       //SW
            x00--;
            y00--;
        }
    }
    else{
        if(d>0){    //S
            y11--;
        }
        else{       //SW
            x11--;
            y11--;
        }
    }
    }


void drawline6(int x0,int y0,int x1,int y1){
    glColor3d(0,1,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = dy+2*dx;
    if(type == 1){
        if(d<0){    //S
            y00--;
        }
        else{       //SE
            x00++;
            y00--;
        }
    }
    else{
        if(d<0){    //S
            y11--;
        }
        else{       //SE
            x11++;
            y11--;
        }
    }

    }


void drawline7(int x0,int y0,int x1,int y1){
    glColor3d(1,1,.25);
    int dx = x1-x0;
    int dy = y1-y0;
    int d = 2*dy+dx;
    if(type==1){
        if(d>0){    //E
            x00++;
        }
        else{       //SE
            x00++;
            y00--;
        }
    }
    else{
        if(d>0) {  //E
            x11++;
        }
        
        else{       //SE
            x11++;
            y11--;
        }
    }
    
}



void findzone(int x0,int y0,int x1,int y1){
    int dx = x1-x0;
    int dy = y1-y0;
    if (dx >= 0 && dy >= 0){        //zone 0 or zone 1
        if (dx>=dy) {                //zone 0
            drawline0( x0, y0, x1, y1);
        }
        else drawline1( x0, y0, x1, y1);        //zone 1
    }
    else if (dx<0 && dy>=0){        //zone 2 or zone 3
        if(abs(dx)>=dy) {           //zone 3
            drawline3( x0, y0, x1, y1);     
            
            }   
        else {       //zone 2
            drawline2( x0, y0, x1, y1);
                   
        }
    }
    else if (dx<0 && dy<0){         //zone 4 or zone 5
        if(abs(dx)>=abs(dy)) drawline4( x0, y0, x1, y1);        //zone 4
        else drawline5( x0, y0, x1, y1);      //zone 5
    }
    else{                            // zone 6 or zone 7
    
        if(dx>=abs(dy)) drawline7( x0, y0, x1, y1);        //zone 7
        else drawline6( x0, y0, x1, y1);              //zone 6
    }
    
    return;
}









void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int mx = mousex;
        int my = mousey;
        glutPostRedisplay();
        if (flag == 2){
            flag = 0;
        }
        flag++;
        if (flag == 1) {
            x00 = mx-320;
            y00 = -my+240;
        }
        else if (flag == 2)
        {
            x11 = mx-320;
            y11 = -my+240;
            flag2 = 1;
        }
    }
}

void draw8way(int x,int y,int x0,int y0){
    int a=x0;
    int b=y0;
    glVertex2i(x+a, y+b);
    glVertex2i(x+a, -y+b);
    glVertex2i(-x+a, y+b);
    glVertex2i(-x+a, -y+b);
    glVertex2i(y+a, x+b);
    glVertex2i(y+a, -x+b);
    glVertex2i(-y+a, x+b);
    glVertex2i(-y+a, -x+b);

}

void drawCircle(int r,int x0,int y0){
    int x = 0;
    int y = r;

    int d = 5 - 4*r;
    draw8way(x,y,x0,y0);
    while(y>x)
    {
        if (d<=0){          //dE
            x++;
            d += 8*x+12;
        }   

        else{               //dSE
            x++;
            y--;
            d += 8*x - 8*y + 20;
        }
        draw8way(x,y,x0,y0);    
    }
}



void reshape(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2,WIDTH/2-1,-HEIGHT/2,HEIGHT/2-1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glPointSize(2.0);
}

void Timer(int ex)
{


    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);
}


void circle(int p,int m)
{
    int x=0,y,d,r;
    r=m;
    y=r;
    d=3-2*r;
    while(x<=y)
    {
        glVertex2i(x,y+p);
        glVertex2i(y,x+p);
        glVertex2i(-x,y+p);
        glVertex2i(-y,x+p);
        glVertex2i(-x,-y+p);
        glVertex2i(-y,-x+p);
        glVertex2i(y,-x+p);
        glVertex2i(x,-y+p);
        if(d<0)
            d=d+4*x+6;
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}

void drawzone(){
    for (int i=-400;i<400;i++) glVertex2i(i, i);
    for (int i=-400;i<400;i++) glVertex2i(-i, i);
    for (int i=-400;i<400;i++) glVertex2i(i, 0);
    for (int i=-400;i<400;i++) glVertex2i(0, i);
    return;
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_POINTS);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    //drawzone();

    if (flag >= 1){
        drawCircle(RAD,x00,y00);
    }
    if (flag == 2){
        //flag = 0;
        drawCircle(RAD,x11,y11); 
    }
    if (flag2 == 1){
        ax0[p]=x00;
        ax1[p]=x11;
        ay0[p]=y00;
        ay1[p]=y11;
        p++;
        if (isCollide() == false){
            type = 1;
            findzone(x00,y00,x11,y11);
            type = 2;
            findzone(x11,y11,x00,y00);
        }
        else{
            flag2 = 2;
            p--;
        }
    }

    if (flag2 == 2)
    {
        if (p== -1) {
            flag2 = 1;
        }
        else{
            x00 = ax0[p];
            x11 = ax1[p];
            y00 = ay0[p];
            y11 = ay1[p];
            p--;
        }
        /* code */
    }

   

    glEnd();
    glutSwapBuffers();

}

void idle(void)
{
    /* do nothing */
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow(argv[0]);
    init();
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(0,Timer,0);
    glutMainLoop();
    return(1);
}
