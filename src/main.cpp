#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "animation/AnimationSystem.h"
#include "ParticleSystem.h"
#include "util/text.h"

#define PARTICLE_COUNT 2000

ParticleSystem* pSys = NULL;

char* buf = new char[50];

int sWidth = 800;
int sHeight = 600;
int mouseX, mouseY;
float pitch, yaw;
bool bZoom = false;
float zoom = 0.0;

void display();
void idle();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void specKeyDown(int, int, int);
void specKeyUp(int, int, int);
void keyLoop(int value);
void mouse(int, int, int, int);
void mouseMotion(int, int);

// UP DOWN LEFT RIGHT
bool arrowKeys[4] = {false, false, false ,false};

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize(sWidth, sHeight);
   glutCreateWindow("Particle System Demo");
   glEnable(GL_DEPTH_TEST);

   glClearColor(0.1, 0.1, 0.1, 0.0);

   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specKeyDown);
   glutSpecialUpFunc(specKeyUp);
   glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
   glutReshapeFunc(reshape);

   glutTimerFunc(10.0, keyLoop, 0);


   // try to create an animation system
   AnimationSystem* sys = AnimationSystem::getInstance();
   pSys = new ParticleSystem(PARTICLE_COUNT);
   //pSys->m_globalForces.push_back(Vec3f(0.0, -10.0, 0.0));
   sys->addSystem(pSys);

   glutMainLoop();

   printf("WTF!\n");
   return 0;
}

//-----------------------------------------------------------------------------
// Reshape
void reshape(int x, int y)
{
   sWidth = x;
   sHeight = y;
   glViewport(0,0,x,y);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluOrtho2D(-100, 100, -100, 100);
   gluPerspective(45, 1, 1, 1000);
   //gluOrtho2D(-10, 10, -10, 10);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   /* Front
   gluLookAt(0,500,0,
            0,0,0,
            0,0,1);
            // */
   /* Top
   gluLookAt(0,0,500,
            0,0,0,
            0,1,0);
   // */
   ///* Persp
   gluLookAt(0,500,500,
            0,0,100,
            0,-11,0);
   // */
}

//-----------------------------------------------------------------------------
// Display
void display()
{
   //printf("IM DISPLAYING!\n");
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glRotatef(pitch, 1.0, 0.0, 0.0);
   glRotatef(yaw, 0.0, 0.0, 1.0);

   glTranslatef(zoom, 0.0, 0.0);
   // Draw the particle system
   pSys->draw();

   glPopMatrix();

   //fps();


   glColor3f(1.0,1.0,1.0);
   sprintf(buf, "Max Weight ('-'/'+')  [ %f ]", pSys->maxWeight);
   drawText(1,2, GLUT_BITMAP_HELVETICA_10, buf);
   sprintf(buf, "Drag Coefficient ('z'/'x')  [ %f ]", pSys->dragCoef);
   drawText(1,4, GLUT_BITMAP_HELVETICA_10, buf);
   sprintf(buf, "Wind Speed ('a'/'s')           [ %f ]", pSys->windSpeed);
   drawText(1,6, GLUT_BITMAP_HELVETICA_10, buf);
   sprintf(buf, "Wind Rise ('q'/'w')             [ %f ]", pSys->windRise);
   drawText(1,8, GLUT_BITMAP_HELVETICA_10, buf);

   sprintf(buf, "Particle count   [ %d ]\n", PARTICLE_COUNT);
   drawText(1, 98, GLUT_BITMAP_HELVETICA_10, buf);




   glutSwapBuffers();
}

//-----------------------------------------------------------------------------
// Idle
void idle()
{
   glutPostRedisplay();
}

//-----------------------------------------------------------------------------
// Keyboard
void keyboard(unsigned char key, int x, int y)
{
   switch(key)
   {
      case 27:
         exit(0);
         break;
      case 'q':
         pSys->windRise -= 5.0;
         break;
      case 'a':
         pSys->windSpeed -= 5.0;
         break;
      case 'z':
         pSys->dragCoef -= 0.01;
         break;
      case 'w':
         pSys->windRise += 5.0;
         break;
      case 's':
         pSys->windSpeed += 5.0;
         break;
      case 'x':
         pSys->dragCoef += 0.01;
         break;
      case '+':
      case '=':
         pSys->maxWeight += 1.0;
         pSys->updateWeight();
         break;
      case '-':
         pSys->maxWeight = (pSys->maxWeight <= 1.0) ? 1.0 : (pSys->maxWeight - 1.0);
         pSys->updateWeight();


   }
}

void specKeyDown(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_UP:
         arrowKeys[0] = true;
         pSys->windCenter.y += 1.1;
         break;
      case GLUT_KEY_DOWN:
         arrowKeys[1] = true;
         pSys->windCenter.y -= 1.1;
         break;
      case GLUT_KEY_LEFT:
         arrowKeys[2] = true;
         pSys->windCenter.x -= 1.1;
         break;
      case GLUT_KEY_RIGHT:
         arrowKeys[3] = true;
         pSys->windCenter.x += 1.1;
         break;
      default:
         break;
   }
}

void specKeyUp(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_UP:
         arrowKeys[0] = false;
         break;
      case GLUT_KEY_DOWN:
         arrowKeys[1] = false;
         break;
      case GLUT_KEY_LEFT:
         arrowKeys[2] = false;
         break;
      case GLUT_KEY_RIGHT:
         arrowKeys[3] = false;
         break;
      default:
         break;
   }

}

void keyLoop(int value)
{
   if (arrowKeys[0])
      pSys->windCenter.y -= 0.1;
   if (arrowKeys[1])
      pSys->windCenter.y += 0.1;
   if (arrowKeys[2])
      pSys->windCenter.x += 0.1;
   if (arrowKeys[3])
      pSys->windCenter.x -= 0.1;

   glutTimerFunc(10.0, keyLoop, 0);
}


void mouse(int button, int state, int x, int y)
{

   switch(button)
   {
      case GLUT_RIGHT_BUTTON:
         mouseX = x;
         mouseY = y;
         break;
      case GLUT_LEFT_BUTTON:
         bZoom = (state == GLUT_DOWN) ? true : false;
         break;
   }

}

void mouseMotion(int x, int y)
{
   if (bZoom)
   {
      zoom += (x-mouseX);
   }
   else
   {
      yaw += (x-mouseX);
      pitch -= (y-mouseY);
   }

   mouseX = x;
   mouseY = y;
}
