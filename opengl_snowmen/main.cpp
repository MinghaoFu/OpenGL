#include <iostream>
#include "SOIL.h"
#include <GL/glut.h>
#include <math.h>

//Public variable
//Angle of rotation for the camera direction(Y rotating to top angle)
float angle = 0.0;
//Actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
//XZ position of the camera
float x = 0.0f, z = 5.0f;

bool light = false;

// Set light parameter
GLfloat LightAmbient[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightPosition[] = {0.0f,0.0f,10.0f,1.0f};

GLfloat gray[] = {0.9f, 0.9f, 0.9f, 1.0f};

void  changeSize(GLsizei w, GLsizei h)
{
    GLfloat fAspect;

    // Prevent divide from zero
    if (h == 0) {
        h = 1;
    }

    // Set viewport to window dimensions
    glViewport(0,0,w,h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(60.0f,fAspect,1.0,400.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawSnowMan()
{
    //Set polygon color
    glColor3f(1.0f,1.0f,1.0f);

    //Draw body
    glTranslatef(0.0f,0.75f,0.0f);
    glutSolidSphere(0.75f,20,20);

    //Draw head
    glTranslatef(0.0f,1.0f,0.0f);
    glutSolidSphere(0.25f,20,20);

    //Draw eyes
    //OpenGL keeps a stack of matrix to quickly apply and remove transformations.
    //glPushMatrix copies the top matrix and pushes it onto the stack, while glPopMatrix
    //pops the top matrix off the stack. All transformation functions function on the top
    // matrix, and the top matrix is what all rendering commands use to transform their data.
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f,0.10f,0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f,0.0f,0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

    //Draw Nose
    glColor3f(1.0f,0.5f,0.5f);
    glRotatef(0.0f,1.0f,0.0f,0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}

void renderScene(void)
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Reset transformations
    glLoadIdentity();

    //Set the camera
    gluLookAt(x,1.0f,z,
              x+lx,1.0f,z+lz,
              0.0f,1.0f,0.0f);

    //Draw ground
    glColor3f(0.9f,0.9f,0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f,0.0f,-100.0f);
        glVertex3f(-100.0f,0.0f,100.0f);
        glVertex3f(100.0f,0.0f,100.0f);
        glVertex3f(100.0f,0.0f,-100.0f);
    glEnd();

    //Draw 36 snowmen
    for (int i = -3; i < 3; i++) {
        for (int j = -3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i*10.0,0,j*10.0);
            drawSnowMan();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

int InitGL(GLvoid)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.5f);
    glClearDepth(1.0f);
    glEnable(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
    glLightfv(GL_LIGHT1,GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT, GL_DIFFUSE,gray);

    return true;
}

void processNormalKeys(unsigned char key,int x,int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'l':
            light = !light;
            light? glEnable(GL_LIGHTING):glDisable(GL_LIGHTING);
            break;
    }
}

void processSpecialKeys(int key, int xx, int yy)
{
    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT:
            angle -= 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT:
            angle += 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP:
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN:
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

int main(int argc, char **argv) {

    //init Glut and create window
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // OpenGl init
    glEnable(GL_DEPTH_TEST);

    InitGL();
    // Enter GLUT event processing cycle
    glutMainLoop();
    return 0;
}
