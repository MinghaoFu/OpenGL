#include <iostream>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLfloat xrot;       // X rotation
GLfloat yrot;       // y rotation
GLfloat xspeed;     // X rotation speed
GLfloat yspeed;     // Y rotation speed
GLfloat z = -5.0f;  // Depth into the screen

bool light;
GLuint filter;
GLuint texture[2];

GLfloat gray[] = {0.9f, 0.0f, 0.0f, 1.0f};



void changeSize(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    float ratio = w * 1.0 / h;

    // Use the projection matrix
    glMatrixMode(GL_PROJECTION);

    // Reset matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0,0,w,h);

    // Set the correct perspective
    gluPerspective(45,ratio,1,100);

    // Get back to the modelview
    glMatrixMode(GL_MODELVIEW);
}

int LoadGLTextures()
{
    for (int i = 0; i < 2; i++)
    {
        texture[i] = SOIL_load_OGL_texture("lena.png",SOIL_LOAD_AUTO,
                                           SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    }
    if (texture[0] == 0)
    {
        return false;
    }
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    if (texture[1] == 0)
    {
        return false;
    }
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    return true;
}


void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,z);

    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);

    glBindTexture(GL_TEXTURE_2D,texture[filter]);

    glColor4f(1.0f,0.0f,0.0f,1.0f);
    glutSolidCube(1.0);

    glBegin(GL_QUADS);
        // Front face
        glNormal3f(0,0,1);
        glTexCoord2f(0.0,0.0); glVertex3f(-1.0,-1.0,1.0);
        glTexCoord2f(1.0,0.0); glVertex3f(1.0,-1.0,1.0);
        glTexCoord2f(1.0,1.0); glVertex3f(1.0,1.0,1.0);
        glTexCoord2f(0.0,1.0); glVertex3f(-1.0,1.0,1.0);
        // Back face
        glNormal3f(0,0,-1);
        glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
        glTexCoord2f(1,1); glVertex3f(-1,1,-1);
        glTexCoord2f(0,1); glVertex3f(1,1,-1);
        glTexCoord2f(0,0); glVertex3f(1,-1,-1);
        // Top face
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(-1,1,-1);
        glTexCoord2f(0,0); glVertex3f(-1,1,1);
        glTexCoord2f(1,0); glVertex3f(1,1,1);
        glTexCoord2f(1,1); glVertex3f(1,1,-1);
        // Bottom face
        glNormal3f(0,-1,0);
        glTexCoord2f(1,1); glVertex3f(-1,-1,-1);
        glTexCoord2f(0,1); glVertex3f(1,-1,-1);
        glTexCoord2f(0,0); glVertex3f(1,-1,1);
        glTexCoord2f(1,0); glVertex3f(-1,-1,1);
        // Right face
        glNormal3f(1,0,0);
        glTexCoord2f(1,0); glVertex3f(1,-1,-1);
        glTexCoord2f(1,1); glVertex3f(1,1,-1);
        glTexCoord2f(0,1); glVertex3f(1,1,1);
        glTexCoord2f(0,0); glVertex3f(1,-1,1);
        // Left face
        glNormal3f(-1,0,0);
        glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
        glTexCoord2f(1,0); glVertex3f(-1,-1,1);
        glTexCoord2f(1,1); glVertex3f(-1,1,1);
        glTexCoord2f(0,1); glVertex3f(-1,1,-1);
    glEnd();
    glutSwapBuffers();

    xrot += xspeed;
    yrot += yspeed;
}

int InitGL(GLvoid)
{
    if (!LoadGLTextures())
    {
        return false;
    }

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.5f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Set light parameter
    GLfloat LightAmbient[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat LightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat LightPosition[] = {0.0f,0.0f,2.0f,1.0f};

    glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
    glLightfv(GL_LIGHT1,GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);

    //glMaterialfv(GL_FRONT, GL_DIFFUSE,gray);

    return true;
}


void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'l':
            light = !light;
            light? glEnable(GL_LIGHTING):glDisable(GL_LIGHTING);
            break;
        case 'f':
            filter += 1;
            if (filter > 1)
            {
                filter = 0;
            }
            printf("%d",filter);
            break;
    }
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_PAGE_UP:
            z -= 0.02f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            z += 0.02f;
            break;
        case GLUT_KEY_UP:
            xspeed += 0.01f;
            break;
        case GLUT_KEY_DOWN:
            xspeed += 0.01f;
            break;
        case GLUT_KEY_LEFT:
            yspeed -= 0.01f;
            break;
        case GLUT_KEY_RIGHT:
            yspeed += 0.01f;
            break;
    }
}



int main(int argc, char **argv) {

    //Init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,640);
    glutCreateWindow("Rotate Cube");

    // Callbacks
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    InitGL();

    glutMainLoop();

    return 0;
}
