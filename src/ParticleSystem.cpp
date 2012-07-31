#include "ParticleSystem.h"
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <GL/glut.h>

#define RAND(x) (rand() % ((int)x*(int)x)/x)
#define PI 3.14159265 
//#define WIND_POWER 200.0
#define MAX_HEIGHT 200

//#define MAX_WEIGHT 10.0
//#define ROT_SPEED 50.0
//#define MAX_DIST 300.0
//#define WIND_RISE 200.0
//#define DRAG_COEF 0.01

//Vec3f windCenter = Vec3f(-200.0,0.0,0.0);

using namespace std;

ParticleSystem::ParticleSystem(int nCount) :
   m_maxParticles(nCount),
   windRise(1.0),
   windSpeed(50.0),
   dragCoef(0.03),
   maxWeight(1.0),
   windCenter(Vec3f())
{

   for( int i = 0; i < m_maxParticles; i++)
   {
      Vec3f pos = Vec3f();
      pos.x = rand() % 500 - 250;
      pos.y = rand() % 500 - 250;
      //pos.x = 1.0;
      //pos.y = 0;
      pos.z = rand() % MAX_HEIGHT + 1;
      //pos.z = 0.0;

      Vec3f vel = Vec3f();
      /*
      //(pos*-1).cross(Vec3f(0.0,0.0,1.0));
      vel.normalize();

      float rad = rand() % 50 + 10;//10.0;
      float period = PERIOD;//rand() % 10 / 2.0 + 1.0;
      vel *= 2.0 * PI * rad / period;
      vel = Vec3f();
      */

      // random weight
      float weight = RAND(maxWeight) + 1.0;
      //float weight = 1;

      Particle* p = new Particle(pos, weight, vel);
      m_particles.push_back(p);
   }

}


void ParticleSystem::update(int timeElapsed)
{
   //printf("PS: updated [%d]\n", timeElapsed);


   // apply forces??
   /*
   vector<Vec3f>::iterator i;
   for( i = m_globalForces.begin(); i != m_globalForces.end(); i++ )
   {
      Vec3f f = *itr;
   }
   */


   // update the particles
   vector<Particle*>::iterator itr;
   for( itr = m_particles.begin(); itr != m_particles.end(); itr++)
   {
      Particle* p = *itr;

      // add the global forces
      /*
      p->forces.insert( p->forces.end(),
                        m_globalForces.begin(),
                        m_globalForces.end());
                        */

      // add a center point gravity
      /*
      Vec3f center = p->position * -1.0;
      float dist = center.length();
      center.normalize();

      Vec3f up = Vec3f(0.0, 0.0, 1.0);

      Vec3f ortho = center.cross(up);
      ortho.normalize();
      */



      //p->forces.push_back(center*(5.0/log(dist+2)));
      //p->forces.push_back(ortho);
      
      
      //Vec3f pos = p->position + p->vel*t + 

      // v = 2PI R / T
      // a = 2PI v / T
      //printf( "\t%f\n", p->velocity.length());
      
      // 1- (ln(1/(x+1)) + exp(x/5))
      
      // WIND FORCE
      //
      //float x = dist/WIND_RAD * 5;
      //Vec3f wForce = Vec3f();
      
      /*
      if( dist < WIND_RAD)
      {
         wForce = ortho*( 1- (log(1.0/(x+1.0)) + exp(x/5.0)));
      }
      */




      //Vec3f aForce = center*p->velocity.length()*2.0*PI / (dist*dist);
      //Vec3f aForce = center * 
     
      /*
      printf("Particle: %f, %f, %f\n\t%f, %f, %f\n\t%f, %f, %f\n", 
            p->position.x, p->position.y, p->position.z,
            p->velocity.x, p->velocity.y, p->velocity.z,
            aForce.x, aForce.y, aForce.z);
            //*/
      //p->forces.push_back(aForce);
      //p->forces.push_back(wForce);

      //----------------------------------------------------
      /* ATTEMPT 1
      Vec3f pos = p->position * -1;
      pos.z = 0;
      //pos.normalize();

      float distA = pos.length();
      float height = abs(p->position.z)+1;
      Vec3f axis = Vec3f(0.0, 0.0, WIND_POWER*WIND_POWER/(distA*distA));//WIND_POWER*2/sqrt(dist));// * (height*height)/(dist));


      Vec3f targetVel = axis.cross(pos);

      Vec3f radialVel = targetVel.normal() * max(targetVel.length() - p->velocity.length(), 0.0f);
      //Vec3f centri = p->position.cross(p->velocity/height);
      //Vec3f centri = Vec3f(0.0,0.0,1.0).cross(ortho*p->velocity.length());
      Vec3f centri = Vec3f(0.0,0.0,1.0).cross(ortho*radialVel.length());

      //p->forces.push_back(radialVel);
      p->velocity = radialVel;
      p->forces.push_back(centri);
      p->forces.push_back(pos.normal() * (WIND_POWER*WIND_POWER)/(p->position.length()));
      p->forces.push_back(pos.normal() * (WIND_POWER*WIND_POWER)/height);

      //p->forces.push_back(Vec3f(0.0, -10.0, 0.0));
      //*/

      //----------------------------------------------------
      ///* ATTEMPT 2

      
      float height = abs(p->position.z)+1;

      float velSq = p->velocity.squareLength();


      Vec3f eyePos = p->position - windCenter;
      Vec3f pos = eyePos;
      pos.z = 0;

      float posLen = pos.length();

      Vec3f axis = Vec3f(0.0, 0.0, windSpeed * 1/sqrt(posLen+1));// max((1 - pos.squareLength()/(MAX_DIST*MAX_DIST)),0.0));
      Vec3f rad = pos;
      rad.normalize();
      rad *= sqrt(height);// + (rand() % MAX_HEIGHT/2);

      Vec3f targetVel = axis.cross(rad);
      //targetVel.z += WIND_RISE*1.0/dist*dist;
      //Vec3f vel = targetVel.normal() * max(targetVel.length() - p->velocity.length(), 0.0f);
      Vec3f accel = axis.cross(targetVel);

      p->velocity = targetVel;
      //p->forces.push_back(vel);
      p->forces.push_back(accel);

      // rising force
      //Vec3f rise = Vec3f(0.0, 0.0, (windRise*windRise*windRise)/(eyePos.length()*height*(p->velocity.length()+1)));//*1.0/(eyePos.squareLength()));
      Vec3f rise = Vec3f(0.0, 0.0, sqrt(windRise*windRise*(velSq/(height))));
      p->forces.push_back(rise);

      // Drag
      //Vec3f drag = (p->velocity.normal() * (velSq) * dragCoef);
      //drag *= -0.5;
      //p->forces.push_back(drag);

      //*/

      // gravity
      p->forces.push_back(Vec3f(0.0,0.0, -10.0*p->mass));




      
      p->update(timeElapsed);
   }

   //windCenter.x += 0.5;


}

void ParticleSystem::updateWeight()
{
   vector<Particle*>::iterator itr;
   for( itr = m_particles.begin(); itr != m_particles.end(); itr++)
   {
      (*itr)->mass = RAND(maxWeight) + 1;
   }
}

void ParticleSystem::draw()
{

   // draw all the particles
   vector<Particle*>::iterator itr;
   for( itr = m_particles.begin(); itr != m_particles.end(); itr++)
   {
      Particle* p = *itr;
      // height color
      glColor3f(1.0, p->position.z/MAX_HEIGHT, 0.0);
      // mass color
      //float c = p->mass/(maxWeight);
      //glColor3f(c, 1-c, 0.0);
      (*itr)->draw();
   }
   
}

