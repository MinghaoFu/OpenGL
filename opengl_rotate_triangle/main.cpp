#include <GL/glut.h>
#include <stdlib.h>

GLfloat angle = 0.0;
GLfloat red = 1.0f,green = 1.0f,blue = 1.0f;

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}


void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle,0.0f,1.0f,0.0f);
    glColor3f(red,green,blue);

    glBegin(GL_TRIANGLES);
        glVertex3f(-1,-1,0);
        glVertex3f(1,0,0);
        glVertex3f(0,1,0);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void SetupRc(void)
{
    glClearColor(0.6f,0.4f,0.4f,1.0f);
    glColor3f(1.0f,0.0f,0.0f);
}

void changeSize(int w, int h)
{
    GLfloat aspectRatio;
    if (h == 0)   h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w < h) {
        glOrtho(-1.0,1.0,-1.0/aspectRatio,1.0/aspectRatio,1.0,-1.0);
    }
    else {
        glOrtho(-1.0*aspectRatio,1.0*aspectRatio,-1.0,1.0,1.0,-1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int value)
{
    angle += 2.0f;
    //Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(23,TimerFunction,1);
}

void processNormalKeys(unsigned char key,int x,int y)
{
    if (key == 27) {
        exit(0);
    }
}

void processSpecialKeys(int Key,int x,int y)
{
    switch (Key) {
        case GLUT_KEY_F5:
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case GLUT_KEY_F6:
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case GLUT_KEY_F7:
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        case GLUT_KEY_F8:
            red = 0.5;
            green = 0.5;
            blue = 0.3;
            break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(200,200);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("Rotate triangle");

    //Register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutTimerFunc(23,TimerFunction,1);

    //keyboards reacting
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    //Setup Rendering space
    SetupRc();
    glutMainLoop();
    return 0;
}