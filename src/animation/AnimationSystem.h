//-----------------------------------------------------------------------------
// Main Animation manager class. Handles the timestep.
// Add an AnimatedSystem and it'll handle the updates.
//-----------------------------------------------------------------------------

#ifndef __ANIMATION_SYSTEM_H__
#define __ANIMATION_SYSTEM_H__

#include "AnimatedSystem.h"
#include <vector>

#define TIMESTEP 10

class AnimationSystem
{

public:
   static AnimationSystem* getInstance();

   void addSystem(AnimatedSystem*);
   void animate(int value);

protected:
   AnimationSystem();

   std::vector<AnimatedSystem*> m_animSystems;

   int lastTime;

private:
   //static AnimationSystem* m_pInstance = 0;
};

#endif
