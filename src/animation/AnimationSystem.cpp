#include "AnimationSystem.h"
#include <GL/glut.h>
#include <stdio.h>

using namespace std;

void animLoop(int value)
{
   glutTimerFunc(TIMESTEP, animLoop, 0);

   AnimationSystem::getInstance()->animate(value);
}

AnimationSystem::AnimationSystem()
{
   glutTimerFunc(TIMESTEP, animLoop, 0);
   lastTime = glutGet(GLUT_ELAPSED_TIME);
}

AnimationSystem* AnimationSystem::getInstance()
{
   /* // thread safe method
   if(!m_pInstance)
      m_pInstance = new AnimationSystem();

   return m_pInstance;
   */

   // note: not thread safe!
   static AnimationSystem inst;
   return &inst;
}

void AnimationSystem::addSystem(AnimatedSystem* sys)
{
   m_animSystems.push_back(sys);
}

void AnimationSystem::animate(int value)
{
   //printf("STEP[%d].", glutGet(GLUT_ELAPSED_TIME) - lastTime);
   //fflush(stdout);

   int newTime = glutGet(GLUT_ELAPSED_TIME);
   
   vector<AnimatedSystem*>::iterator itr;
   for (itr = m_animSystems.begin(); itr != m_animSystems.end(); itr++)
   {
      AnimatedSystem* s = *itr;
      s->update(newTime-lastTime);
   }
   /*
   for each(AnimatedSystem s in m_animSystems)
   {
      s->update(newTime-lastTime);
   }
   */
   
   
   lastTime = newTime;
}



