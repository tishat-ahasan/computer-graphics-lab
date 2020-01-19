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

static int slices = 16;
static int stacks = 16;

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
       glVertex2i(x, y); 
    }
}

void drawline1(int x0,int y0,int x1,int y1){
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

void drawzone(){
    for (int i=-200;i<200;i++) glVertex2i(i, i);
    for (int i=-200;i<200;i++) glVertex2i(-i, i);
    return;
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
    
    findzone(0,0,50,-10);
    glColor3d(1,0,0);
    findzone(0,0,-50,-1);
    
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

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
