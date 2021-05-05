#include <iostream>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <math.h>

using namespace std;

#define MAX_PARTICLES 200
#define MAX_PARTICLESONS 800
#define PI 3.14159f
#define RHO 50
#define LIFE 3.0f
#define TIME 0.01f

float windowHeight, windowWidth;
int texture[1];
typedef struct
{
	float life, init_life, speed_aging;
	float r,g,b;
	float x,y,z;
	float vx,vy,vz;
	float ax,ay,az;

	int update_times;
	typedef struct
	{
		float life, init_life, speed_aging;
		float x,y,z;
		float r,g,b;
		float vx,vy,vz;
		float ax,ay,az;
	}particleSon;
	
	particleSon particleSons[MAX_PARTICLESONS];
}particle;

particle particles[MAX_PARTICLES];

void ChangeSize(int w, int h)
{
	float aspectRatio;

	if (h == 0)
	{
		h = 1;
	}

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (float)w/ (float)h;

	if (w <= h)
	{
		windowHeight = 100;
		windowWidth = 100/aspectRatio;
		glOrtho(-windowHeight, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	if (texture[1] == 0)
	{
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	return true;
}

int InitialParticleSystem()
{
	if (!LoadGLTextures)
	{
		cout << "Could not load teture..." << endl;
		return false;
	}
	glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.5f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);glEnable(GL_TEXTURE_2D);


	float theta, phi, rho;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].init_life  = LIFE + rand()%10/10.0;
		particles[i].life = particles[i].init_life;
		particles[i].speed_aging = TIME;

		particles[i].r = rand()%10 / 10.0f;
		particles[i].g = rand()%10 / 10.0f;
		particles[i].b = rand()%10 / 10.0f;

		particles[i].x = 0.0f;
		particles[i].y = 50.0f;
		particles[i].z = 0.0f;
		
		particles[i].update_times = 0;

		theta = (rand() % 90 + 45) * PI /180;
		phi = 90 * PI / 180;
		rho = rand() % RHO;
		
		particles[i].vx = float(sinf(phi) * cos(theta) * rho);
		particles[i].vy = float(sinf(phi) * sin(theta) * rho);
		particles[i].vz = float(cosf(phi) * rho);

		particles[i].ax = 0.0f;
		particles[i].ay = -30.0f;
		particles[i].az = 0.0f;

		for (int j = 0; j < MAX_PARTICLESONS; j++)
		{
			float a = rand() % 360 * PI/180.0f;
			float b = rand()%10/10.0f;
			particles[i].particleSons[j].x = particles[i].x + b*cosf(a);
			particles[i].particleSons[j].y = particles[i].y + b*sinf(a);
			particles[i].particleSons[j].z = particles[i].z;
		}
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	return true;
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		float x = particles[i].x;
		float y = particles[i].y;
		float z = particles[i].z;

glColor4f(particles[i].r,particles[i].g,particles[i].b,particles[i].life);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(1,1);glVertex3f(x+0.25f,y+0.25f,z); // Top Right
			glTexCoord2d(0,1);glVertex3f(x-0.25f,y+0.25f,z); // Top Left
			glTexCoord2d(1,0);glVertex3f(x+0.25f,y-0.25f,z); // Bottom Right
			glTexCoord2d(0,0);glVertex3f(x-0.25f,y-0.25f,z); // Bottom Left
		glEnd();
		
		for (int j = 0; j < MAX_PARTICLESONS; j++)
		{
			float x1 = particles[i].particleSons[j].x;
			float y1 = particles[i].particleSons[j].y;
			float z1 = particles[i].particleSons[j].z;
			glPointSize(0.5f);
			glBegin(GL_POINTS);
			glVertex3f(x1,y1,z1);
			glEnd();
		}
	}

	glutSwapBuffers();
}

void update()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{   
		particles[i].update_times += 1;

		particles[i].x += particles[i].vx * TIME;
		particles[i].y += particles[i].vy * TIME;
		particles[i].z += particles[i].vz * TIME;
		
		particles[i].vx += particles[i].ax * TIME;
		particles[i].vy += particles[i].ay * TIME;
		particles[i].vz += particles[i].az * TIME;

		particles[i].life -= particles[i].speed_aging;
		
		if (particles[i].x >= windowWidth || particles[i].x <= -windowWidth || particles[i].y >= windowHeight || particles[i].y <= -windowHeight)
		{
			float a = rand() % 360 * PI/180.0f;
			float b = rand()%10/10.0f;	
			for (int j = 0; j < MAX_PARTICLESONS; j++)
			{
				particles[i].particleSons[j].x += rand()%10/10.0f-0.5f;
				particles[i].particleSons[j].y += rand()%10/10.0f-1.0f;
				particles[i].particleSons[j].z += 0;
			}
		}
		else
		{
			for (int j = 0; j < MAX_PARTICLESONS; j++)
			{
				particles[i].particleSons[j].x += particles[i].vx * TIME;
				particles[i].particleSons[j].y += particles[i].vy * TIME;
				particles[i].particleSons[j].z += particles[i].vz * TIME;
			}
		}

		for (int j = 0; j < 2*particles[i].update_times; j++)
		{
			particles[i].particleSons[j].x -= particles[i].vx * TIME * (rand()%5/5.0f);
			particles[i].particleSons[j].y -= particles[i].vy * TIME * (rand()%5/5.0f);
			particles[i].particleSons[j].z -= particles[i].vz * TIME * (rand()%5/5.0f);
		}
		
		float theta, phi, rho;
		if (particles[i].life <= 0)
		{
			particles[i].update_times = 1;
			particles[i].init_life = LIFE + rand() % 10 / 10.0;
			particles[i].life = particles[i].init_life;
			particles[i].x = 0.0f;
			particles[i].y = 50.0f;
			particles[i].z = 0.0f;

			for (int j = 0; j < MAX_PARTICLESONS; j++)
			{
				float a = rand() % 360 * PI/180.0f;
				float b = rand()%10/10.0f;
				particles[i].particleSons[j].x = particles[i].x + b*cosf(a);
				particles[i].particleSons[j].y = particles[i].y + b*sinf(a);
				particles[i].particleSons[j].z = particles[i].z;
			}
			
			theta = (rand()%360) * PI /180.0;
			phi = 90 * PI / 180.0;
			rho = rand() % RHO;
			particles[i].vx = float(sinf(phi) * cos(theta) * rho);
			particles[i].vy = float(sinf(phi) * sin(theta) * rho);
			particles[i].vz = float(cos(phi) * rho);
		}
	}
}

void timerFunc(int value)
{
	update();
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}

void Setup(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
			exit(0);
			break;
	}
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("Particle system");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, timerFunc, 1);
	glutKeyboardFunc(processNormalKeys);

	Setup();
	InitialParticleSystem();

	glutMainLoop();
	return 0;	
}



































