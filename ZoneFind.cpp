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

#include <stdlib.h>
#include<stdio.h>
#include <unistd.h>
static int slices = 16;
static int stacks = 16;

int flag = 0;
int x00=0,x11=0,y00=0,y11=0;
/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


/************************************************************************************************************************/
//self code here...







void drawline0(int x0,int y0,int x1,int y1){
	glColor3d(1,0,0);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = 2*dy-dx;
    int dE = 2*dy;
    int dNE = 2*(dy-dx);
    glVertex2i(x, y);
    while(x<x1){
        if(d<0){
            x++;
            d+=dE;
        }
        else{
            x++;
            y++;
            d+=dNE;
        }
        sl
       glVertex2i(x, y); 
    }
}

void drawline1(int x0,int y0,int x1,int y1){
	glColor3d(0,1,0);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = dx-2*dy;
    int dNE = 2*(dy-dx);
    int dN = -2*dx;
    glVertex2i(x, y);
    while(y<y1){
        if(d<0){
            x++;
            y++;
            d+=dNE;
        }
        else{
            y++;
            d+=dN;
        }
       glVertex2i(x, y); 
    }
}

void drawline2(int x0,int y0,int x1,int y1){
	glColor3d(0,0,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = -dy-2*dx;
    int dNW = -2*(dy+dx);
    int dN = -2*dx;
    glVertex2i(x, y);
    while(y<y1){
        if(d>0){
            x--;
            y++;
            d+=dNW;
        }
        else{
            y++;
            d+=dN;
        }
       glVertex2i(x, y); 
    }
}


void drawline3(int x0,int y0,int x1,int y1){
	glColor3d(1,1,0);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = -2*dy-dx;
    int dNW = -2*(dy+dx);
    int dW = -2*dy;
    glVertex2i(x, y);
    while(x>x1){
        if(d<0){
            x--;
            y++;
            d+=dNW;
        }
        else{
            x--;
            d+=dW;
        }
       glVertex2i(x, y); 
    }
}

void drawline4(int x0,int y0,int x1,int y1){
	glColor3d(1,0,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = -2*dy+dx;
    int dSW = -2*(dy-dx);
    int dW = -2*dy;
    glVertex2i(x, y);
    while(x>x1){
        if(d<0){  //dW
            x--;
            d+=dW;
        }
        else{		//dSW
            x--;
            y--;
            d+=dSW;
        }
       glVertex2i(x, y); 
    }
}


void drawline5(int x0,int y0,int x1,int y1){
	glColor3d(1,1,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = -dy+2*dx;
    int dSW = -2*(dy-dx);
    int dS = 2*dx;
    glVertex2i(x, y);
    while(y>y1){
        if(d>0){	//S
            y--;
            d+=dS;
        }
        else{		//SW
            x--;
            y--;
            d+=dSW;
        }
       glVertex2i(x, y); 
    }
}


void drawline6(int x0,int y0,int x1,int y1){
	glColor3d(0,1,1);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = dy+2*dx;
    int dSE = 2*(dy+dx);
    int dS = 2*dx;
    glVertex2i(x, y);
    while(y>y1){
        if(d<0){	//S
            y--;
            d+=dS;
        }
        else{		//SE
            x++;
            y--;
            d+=dSE;
        }
       glVertex2i(x, y); 
    }
}


void drawline7(int x0,int y0,int x1,int y1){
	glColor3d(1,1,.25);
    int dx = x1-x0;
    int dy = y1-y0;
    int x=x0;
    int y=y0;
    int d = 2*dy+dx;
    int dSE = 2*(dy+dx);
    int dE = 2*dy;
    glVertex2i(x, y);
    while(x<x1){
        if(d>0){	//E
            x++;
            d+=dE;
        }
        else{		//SE
            x++;
            y--;
            d+=dSE;
        }
       glVertex2i(x, y); 
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
        if(abs(dx)>=dy) {			//zone 3
        	drawline3( x0, y0, x1, y1);     
        	glVertex2i(-20, 10);
        	}   
        else {       //zone 2
        	drawline2( x0, y0, x1, y1);
        	glVertex2i(-10, 20);       
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


void drawzone(){
    for (int i=-200;i<200;i++) glVertex2i(i, i);
    for (int i=-200;i<200;i++) glVertex2i(-i, i);
    return;
}
// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {
//     if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
//     {
//        double xpos, ypos;
//        //getting cursor position
//        glfwGetCursorPos(window, &xpos, &ypos);
//        cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
//     }
// }


void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int mx = mousex;
        int my = mousey;
        //printf(" c1 %d %d\n",mx-320,my-240);
        glutPostRedisplay();
        flag++;
        if (flag == 1) {
        	x00 = mx-320;
        	y00 = -my+240;
        }
        else if (flag == 2)
        {
        	x11 = mx-320;
        	y11 = -my+240;
        }
    }
    // if (flag == 2)
    // {
    	
    // 	findzone(0,0,50,-10);
    // }
}



int a0=0,a1=0,b0=0,b1=0;
/************************************************************************************************************************/
static void display(void){
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
    glBegin(GL_POINTS);


    drawzone();
    
    //findzone(0,0,50,-10);
    glColor3d(1,0,0);
    if (flag == 2){
    	flag = 0;
    	a0=x00;
    	a1=x11;
    	b0=y00;
    	b1=y11;
    	
    }
    //printf("%d %d %d %d \n", a0,b0,a1,b1);
    findzone(a0,b0,a1,b1);
    glEnd();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

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

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    printf("zone 0 - RED\nzone 1 - GREEN\nzone 2 - BLUE\nzone 3 - YELLOW\nzone 4 - PURPLE\nzone 5 - WHITE\nzone 6 - SKYBLUE\nzone 7 - LIGHT YELLOW\n");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    //if (flag == 2) printf("here\n");

    glutMainLoop();

    return EXIT_SUCCESS;
}
