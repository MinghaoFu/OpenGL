#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

//public variable
//square size and position
GLfloat x =  0.0f;
GLfloat y = 0.0f;
GLfloat rectSize = 25;
GLfloat triangleSize = 25;

//Step size in coordinate
//(number of pixels to move each time)
GLfloat xStep = 1.0f;
GLfloat yStep = 1.0f;

//Keep track of window changing width and height
GLfloat windowWidth;
GLfloat windowHeight;

//draw scene
void render(void)
{
    //clear
    glClear(GL_COLOR_BUFFER_BIT);

    //set drawing color
    glColor3f(1.0,0.0,0.0);

    //Draw a rectangle
    //glRectf(x,y,x + rectSize,y - rectSize);

    glBegin(GL_TRIANGLES);
    glVertex3f(x-triangleSize,y-triangleSize,0);
    glVertex3f(x+triangleSize,y-triangleSize,0);
    glVertex3f(x,y+triangleSize,0);
    glEnd();

    //Flush drawing commands and swap
    glutSwapBuffers();
}

//Set up the rending state
void SetupRC(void)
{
    glClearColor(0,0,1,1);
}

//Timer function
void timerFunction(int value)
{
    //Reverse direction when rectangle touch bounds
    if (x > windowWidth - triangleSize || x < -windowWidth + triangleSize) {
        xStep = -xStep;
    }
    if (y > windowHeight - triangleSize || y < -(windowHeight - triangleSize)) {
        yStep = -yStep;
    }

    //move the square
    x += xStep;
    y += yStep;

    //Check bounds,if in the beginning the square outside the window,
    //x,y will change in a dead loop
    if (x > windowWidth - triangleSize + xStep) {
        x = windowWidth - triangleSize - 1;
    }
    else if (x < -(windowWidth + xStep - triangleSize)) {
        x = -(windowWidth - triangleSize + 1);
    }

    if (y > (windowHeight + yStep)) {
        y = windowHeight - 1;
    }
    else if(y < -(windowHeight - triangleSize + yStep)) {
        y = -windowHeight + triangleSize - 1;
    }

    //Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33,timerFunction,1);
}

//When the window has changed size
void changeSize(int w, int h)
{
    GLfloat aspectRatio;

    //Prevent a divide by zero
    if (h == 0) {
        h = 1;
    }

    //Set viewport to window dimensions
    glViewport(0,0,w,h);

    //Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Establish clipping volume (left,right,bottom,top,near,far)
    aspectRatio = (GLfloat )w / (GLfloat)h;
    if (w <= h) {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100,100,-windowHeight,windowHeight,1,-1);
    }
    else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth,windowWidth,-100,100,1,-1);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {

    //Initialize glut and create window
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    glutCreateWindow("Bounce");
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutTimerFunc(33,timerFunction,1);

    SetupRC();

    glutMainLoop();

    return 0;
}
