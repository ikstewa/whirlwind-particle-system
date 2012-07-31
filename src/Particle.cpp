
#include "Particle.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

Particle::Particle(Vec3f initialPos, float m, Vec3f initVel) :
   position(initialPos),
   velocity(initVel),
   //accel(Vec3f()),
   mass(m)
{
   damp = log(mass+1)+1;
}

void Particle::update(int elapsedTime)
{
   //printf("Particle: update(%d)\n", elapsedTime);

   // sum the forces
   Vec3f f = Vec3f();
   while (!forces.empty())
   {
      f += forces.back();
      forces.pop_back();
   }


   // t in secods
   float t = elapsedTime/1000.0;
   Vec3f accel = f/mass;


   // Update the position
   Vec3f delta = velocity*t + accel*t*t/2.0;
   position += delta;
   velocity += accel*t;

   if (position.z <= 0.0) position.z = 0.0;

   
   /*
   if( position.x <= -50.0)
   {
      //position.x = -50.0 + (-50.0 - position.x);
      position.x = -50;
      velocity.x = -velocity.x / damp;
   }
   */
   
}

void Particle::applyForce(Vec3f f)
{
   printf("Particle: applyFoce(%f,%f,%f)\n", f.x, f.y, f.z);
}

void Particle::draw()
{
   //printf("Particle: draw()\n");

   glPushMatrix();

   glTranslatef(position.x, position.y, position.z);//position.z);
   //printf("pos: %f, %f, %f\n", position.x, position.y, position.z);
   //glRectf(0, 0, 1, 1);
   glutSolidSphere(1.0,3,3);

   glPopMatrix();
}

