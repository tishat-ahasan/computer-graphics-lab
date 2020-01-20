#include<GL/Glut.h> //includes the opengl, glu, and glut header files
#include<stdlib.h> //includes the standard library header file

float r,g,b,x,y;
bool check=true;

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       check=true;
       
        x = mousex;
        y = 480-mousey;
        
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
          
void display(void)
{  
    glColor3f(r,g,b); // sets the current drawing (foreground) color to blue 
    glPointSize(50); // sets the size of points to be drawn (in pixels)
   
    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);//sets the parallel(orthographic) projection of the full frame buffer 

if(check)  
{      
       glBegin(GL_POINTS); // writes pixels on the frame buffer with the current drawing color
       glVertex2i(x,y);   // sets vertex

  glEnd();
}
    glFlush();     // flushes the frame buffer to the screen
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
    glutInitWindowSize(640,480);   //sets the width and height of the window in pixels
    glutInitWindowPosition(10,10);//sets the position of the window in pixels from top left corner 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
    glutCreateWindow("DDA Line Drawing");//creates the window as specified by the user as above.
        
    glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
  
    glutDisplayFunc(display);//links the display event with the display event handler(display)
    glutMouseFunc(mouse);//keyboard event handler
    glutMainLoop();//loops the current event
}
















zone 0 - RED
zone 1 - GREEN
zone 2 - BLUE
zone 3 - YELLOW
zone 4 - PURPLE
zone 5 - WHITE
zone 6 - SKYBLUE
zone 7 - LIGHT YELLOW



