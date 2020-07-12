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
#include <stdio.h>
#include <math.h>
#include<bits/stdc++.h>
using namespace std;

struct point
{
    int x,y;
};


static int slices = 16;
static int stacks = 16;
static int top = 8, bottom = 4, right = 2, left = 1;

int click_flag = 0;

int xmin = -100, xmax = 130, ymin = -100, ymax = 100, flag = 0, x00, y00, x11, y11, flag1 =0 , flagAC = 0, flagPart = 0, flagReg = 0; 
point p0,p1;

point arr[10],up[7],down[7];

/* GLUT callback Handlers */


bool comp(point a,point b){
	if (a.x < b.x) return true;
	else if (a.x == b.x){
		if (a.x == xmin){
			if (a.y<b.y) return true;
		}
		else if (a.x == xmax)
			if (a.y>b.y) return true;
	}
	return false;
}


static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int mx = mousex;
        int my = mousey;
        printf(" c1 %d %d\n",mx-320,-my+240);
        glutPostRedisplay();
        flag++;
        click_flag = 0;
        if (flag % 2 == 1 ) {
        x00 = mx-320;
        y00 = -my+240;
        }
        else if (flag % 2 == 0)
        {
        x11 = mx-320;
        y11 = -my+240;
        flagAC=0,flagPart=0,flagReg=0;
        }
    }
    // if (flag == 2)
    // {
   
    // findzone(0,0,50,-10);
    // }
}

void draw8way(int x,int y,int zone){
    switch(zone){
        case 0:
            //glColor3d(1,1,1);
            glVertex2i(x, y);
            break;
        case 1:
            //glColor3d(0,0,1);
            glVertex2i(y, x);
            break;
        case 2:
            //glColor3d(0,1,0);
            glVertex2i(-y, x);
            break;
        case 3:
            //glColor3d(1,0,0);
            glVertex2i(-x, y);
            break;
        case 4:
            //glColor3d(0,1,1);
            glVertex2i(-x, -y);
            break;
        case 5:
            //glColor3d(0.5,0.5,0);
            glVertex2i(-y, -x);
            break;
        case 6:
            //glColor3d(1,0,1);
            glVertex2i(y, -x);
            break;
        case 7:
            //glColor3d(0.7,0,0.7);
            glVertex2i(x, -y);
            break;

    }

}

void drawline0(int x0,int y0,int x1,int y1,int zone){
    int dx = x1-x0, dy = y1-y0;
    int x=x0,y=y0, d= 2*dy - dx, dE = 2*dy, dNE = 2*(dy-dx);
    draw8way(x, y,zone);
    while(x<x1){
        if(d<0) // east
            x++, d+= dE;
        else // north-east
            x++,y++, d+= dNE;
        draw8way(x, y,zone);
    }

}

void zonefinding(int x0,int y0,int x1,int y1 ){
    int dx = x1-x0, dy = y1-y0;
    if(dx>0 && dy>=0){
        if(abs(dx) > abs(dy)){
            // if(flag2)
            //     printf("Zone 0 white\n");
            return drawline0(x0,y0,x1,y1,0);
        }
        else{
            // if(flag2)
            //     printf("Zone 1 blue\n");
            return drawline0(y0,x0,y1,x1,1);
        }
    }
    if(dx<=0 && dy>0){
        if(abs(dx) > abs(dy)){
            // if(flag2)
            //     printf("Zone 3 red\n");
            return drawline0(-x0,y0,-x1,y1,3);
        }
        else{
            // if(flag2)
            //     printf("Zone 2 green\n");
            return drawline0(y0,-x0,y1,-x1,2);
        }
    }
    if(dx<0 && dy<=0){
        if(abs(dx) > abs(dy)){
            // if(flag2)
            //     printf("Zone 4 sky blue\n");
            return drawline0(-x0,-y0,-x1,-y1,4);
        }
        else{
            // if(flag2)
            //     printf("Zone 5 yellow\n");
            return drawline0(-y0,-x0,-y1,-x1,5);
        }

    }
    else{
        if(abs(dx) > abs(dy)){
            // if(flag2)
            //     printf("Zone 7 violet\n");
            return drawline0(x0,-y0,x1,-y1,7);
        }
        else{
            // if(flag2)
            //     printf("Zone 6 pink\n");
            return drawline0(-y0,x0,-y1,x1,6);
        }
    }


}

bool is_parallel(int x00,int y00,int x11, int y11){
    return (x00 == x11) | (y00 == y11);
 }

 bool is_accepted(int x0,int x1, int y0, int y1){
     if((x0<xmin && x1<xmin) || (y0<ymin && y1<ymin) || (x0>xmax && x1>xmax) || (y0>ymax && y1>ymax))
        return false;
    if(x0<xmin)
        x00 = xmin;
    if(x1<xmin)
        x11 = xmin;
    if(x0>xmax)
        x00 = xmax;
    if(x1>xmax)
        x11 = xmax;
    if(y0<ymin)
        y00 = ymin;
    if(y1<ymin)
        y11 = ymin;
    if(y1>ymax)
        y11 = ymax;
    if(y0>ymax)
        y00 = ymax;
    return true;
 }

 point makeVertex(double t){
     point temp;
     temp.x = p0.x + t*(p1.x-p0.x);
     temp.y = p0.y + t*(p1.y-p0.y);
     return temp;
 }

 void cyrus_beck(double x0,double y0,double x1,double y1){
     //printf("1\n");
     double t,temax = 0, tlmin = 1;
     // top
     t = (ymax-y0)/(y1-y0);
     //printf("%lf\n",t);
     if(y1>y0){ //leaving
        if(t<tlmin)
            tlmin = t;
     }
     else{ //entering
        if(t>temax)
            temax = t;
     }
     //bottom
     t = (ymin-y0)/(y1-y0);
     if(y1>y0){ //entering
         if(t>temax)
            temax = t;
     }
     else{ //leaving
         if(t<tlmin)
            tlmin = t;
     }
     //right
     t = (xmax-x0)/(x1-x0);
     if(x1>x0){ //leaving
        if(t<tlmin)
            tlmin = t;
     }
     else{  //entering
        if(t>temax)
            temax = t;
     }
     //left
     t = (xmin-x0)/(x1-x0);
     if(x1>x0){ //entering
        if(t>temax)
            temax = t;
     }
     else{  //leaving
         if(t<tlmin)
            tlmin = t;
     }
     if(tlmin >= temax){
        glColor3d(1,0,0);
        point newp0 = makeVertex(tlmin);
        point newp1 = makeVertex(temax);

        if (newp0.x > xmin && newp0.x < xmax && newp0.y > ymin && newp0.y < ymax)
            {
            	printf("Hobe na\n");
            }
        else if (newp1.x > xmin && newp1.x < xmax && newp1.y > ymin && newp1.y < ymax)
            {
           		printf("Hobe na\n");
            }
        else{
        	arr[4] = newp0;
        	arr[5] = newp1;
        	// arr[6] = newp1;
        	// arr[7] = newp1;

        	// up[0] = newp0;
        	// up[1] = newp1;

        	// down[0] = newp0;
        	// down[1] = newp1;

        	int u_i = 0;
        	int d_i = 0;

        	for (int i = 0;i<6 ;i++){
        		int d = (arr[i].y - newp0.y) * (newp0.x - newp1.x) - (newp0.y- newp1.y)*(arr[i].x-newp0.x);
        		if (d >= 0){
        			up[u_i++] = arr[i];
        		}
        		if (d<= 0 ){
        			down[d_i++] = arr[i];
        		}
        	}

        	sort(up,up+u_i,comp);
        	sort(down,down+d_i,comp);
        	if (click_flag == 0){
        	printf("Polygon 1\n" );
        	for (int i = 0; i < u_i; ++i)
        	{
        		printf("%d %d\n",up[i].x,up[i].y );
        	}
        	printf("Polygon 2\n" );
        	
        	for (int i = 0; i < d_i; ++i)
        	{
        		printf("%d %d\n",down[i].x,down[i].y );
        	}
        	click_flag = 1;
        }
        	
        }
        zonefinding(newp0.x,newp0.y,newp1.x,newp1.y);
        //printf("%d %d %d %d \n",newp0.x,newp0.y,newp1.x,newp1.y);
        if(temax == 0 && tlmin == 1 && !flagAC){
            flagAC = 1;
            printf("Fully Accepted\n");

        }
        else if(temax!=0 && tlmin!=1 && !flagPart){
            flagPart = 1;
            printf("Partially Accepted\n");
            
        }
     }
     else{
         if(!flagReg){
             flagReg = 1;
             printf("Fully Rejected\n");
         }
     }
 }


static void display(void){
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glPointSize(3);
    glBegin(GL_LINES);
    // glVertex2i(-320, 0);
    // glVertex2i(319, 0);
    // glVertex2i(0, -240);
    // glVertex2i(0, 239);
    glVertex2i(-320, 100); //upper horizontal line
    glVertex2i(319, 100); // upper horizontal line
    glVertex2i(-100, -240); // left vertical line
    glVertex2i(-100, 239); // left vertical line
    glVertex2i(-320, -100); // lower horizontal line
    glVertex2i(319, -100); // lower horizontal line
    glVertex2i(130, -240); // right vertical line
    glVertex2i(130, 239);  // right vertical line
    glEnd();
    
    // glVertex2i(x, y+1);
    // glVertex2i(x, y);
        if(flag % 2 ==0 && flag!=0){
            //glVertex2i(x00, y00);
            //glVertex2i(x11, y11);
            flag1 = 0;
            glPointSize(2);
            glBegin(GL_POINTS);
            zonefinding(x00,y00,x11,y11);
            p0.x = x00, p0.y = y00;
            p1.x = x11, p1.y = y11;
            glEnd();
            if(is_parallel(x00,y00,x11,y11)){
                if(is_accepted(x00,y00,x11,y11)){
                    zonefinding(x00,y00,x11,y11);
                }
                else
                    printf("Rejected\n");
            }
            else{
            	glPointSize(4);
            	glBegin(GL_POINTS);
                cyrus_beck(x00,y00,x11,y11);
                glEnd();
            }
        }
    
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

    arr[0].x = xmin;
    arr[0].y = ymin;

	arr[1].x = xmin;
    arr[1].y = ymax;

	arr[2].x = xmax;
    arr[2].y = ymax;

	arr[3].x = xmax;
    arr[3].y = ymin;

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMainLoop();

    return EXIT_SUCCESS;
}