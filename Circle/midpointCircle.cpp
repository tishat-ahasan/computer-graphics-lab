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
static int slices = 16;
static int stacks = 16;


/************************ Global Veriabls ************************************/

int flag=0;
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




void Timer(int ex)
{


    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);
}




int k =0;

void draw8way(int x,int y,int x0,int y0){
    int a=x0+k,b=y0+k;
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
    int x = 20;
    int y = 0;

    // int d = 5 - 4*r;
    // draw8way(x,y,x0,y0);
    // while(y>x)
    // {
    //     if (d<=0){          //dE
    //         x++;
    //         d += 8*x+12;
    //     }   

    //     else{               //dSE
    //         x++;
    //         y--;
    //         d += 8*x - 8*y + 20;
    //     }
    //     draw8way(x,y,x0,y0);    
    // }

    int d = 5 - 4*r;
    draw8way(x,y,x0,y0);
    while(x>y){
    	if (d>0){  //dNW
    		x--;
    		y++;
    		d += -8*x + 8*y + 20;
    	}

    	else{		//dN
    		y++;
    		d += 8*y+12;
    	}
    	printf(" d = %d\n",d);
    	printf("x = %d,y = %d\n",x,y);
    	draw8way(x,y,x0,y0);
    }



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
        }
    }
}

int a0=0,a1=0,b0=0,b1=0;


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

    if (flag >= 1){
        drawCircle(20,x00,y00);
    }
    if (flag == 2){
        //flag = 0;
        drawCircle(20,x11,y11); 
    }
    // k = (k+1)%100;
    
    glVertex2i(x, y+1);
    glVertex2i(x, y);
    //drawCircle(50);
    //glutTimerFunc(100, display,0);
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
    glutMouseFunc(mouse);
    glutTimerFunc(0,Timer,0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
