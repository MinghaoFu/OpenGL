# OPENGL

## Introduction
Welcome to my OpenGL repository,it includes some ineresting animation code which is completed by OpenGL. 
### What is OpenGL
OpenGL is a Graphics rendering API which is operating system independent, window system  independent and has high-quality color images composed of geometric and image primitives. 
### Install
If you want to run code or study it,you must first install OpenGL.Now lets see How to install OpenGL on out Ubuntu OS. 

Now because GLUT (OpenGL Utility Toolkit) depends upon OpenGL and a number of other related libraries, if we install GLUT then OpenGL will be automatically be installed. 

Run the following commands to install OpenGL. 
```
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
Now to test if OpenGl libraries are working fine on our Linux, we will create a C++ program and test it. 

### A Simple Program
So create a following C++ Program name main.cpp. 
```
#include <GL/glut.h>

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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
```
Now give the command below to compile your code. 
```
$ g++ main.cpp -o testopengl -lglut -lGLU -lGL
```
Of course, you could replace "testopengl" with any other name which you like. 

Now run your OpenGl program with following command.
```
$ ./testopengl
```
OUTPUT: 

![Output Image](http://www.codebind.com/wp-content/uploads/2018/03/opengl_out.png) 

If a window pops up when you run the program, then OpenGL is working on your Ubuntu OS. 

Thanks to http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/. 

### Install SOIL
First you have to install the soil library to use -lSOIL. To install the library use the command.
```
sudo apt-get install libsoil-dev
```
Then place the header file in your project directory and include it in your project file.
```
#include <SOIL/SOIL.h>
```
Now compile the project using gcc along with -lSOIL.

You could test it by running my code in opengl_texture use the command.
```
g++ main.cpp -o -lSOIL -lglut -lGLU -lGL
```
Output:

![Output image](https://github.com/fmhzcm/OpenGL/blob/main/texture/output.png)

### Particle system

Well, particle system is my favourite project--Also, it cost my much time.If you want to compelte it by yourself,a efficient method is to see paper below.

https://www.lri.fr/~mbl/ENS/IG2/devoir2/files/docs/fuzzyParticles.pdf

However,I just add child particles to system,to attach a beautiful scale which the firework is dropping from sky.

If you have some problems with my code,please send email to 1363947999@qq.com. 


