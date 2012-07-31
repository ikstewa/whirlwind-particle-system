//-----------------------------------------------------------------------------
// Represents a particle for the particleSystem :)
//
//-----------------------------------------------------------------------------

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "util/vec3.h"
#include <vector>

class Particle
{
   public:
      Vec3f position;
      Vec3f velocity;
      //Vec3f accel;

      //Vec3f force;
      std::vector<Vec3f> forces;

      float mass;
      float damp;

      Particle(Vec3f p, float m = 1.0, Vec3f initVel = Vec3f());

      void update(int elapsedTime);
      void applyForce(Vec3f);
      void draw();
      

};

#endif
