//-----------------------------------------------------------------------------
// An AnimatedSystem for a particle system. Handles an array of Particles.
//
// Updates and draws are handled through here and distributed to the particles
//-----------------------------------------------------------------------------

#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

#include "Particle.h"
#include "animation/AnimatedSystem.h"
#include <stdio.h>
#include <vector>

class ParticleSystem : public AnimatedSystem
{
   public:

      ParticleSystem(int nCount);

      std::vector<Vec3f> m_globalForces;

      // ---------
      // Whirlwind settings
      float windRise;
      float windSpeed;
      Vec3f windCenter;

      float maxWeight;
      float dragCoef;
      void updateWeight();



      void update(int timeElapsed);
      void draw();

   protected:
      std::vector<Particle*> m_particles;

      int m_maxParticles;
};

#endif
