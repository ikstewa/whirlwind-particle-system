//-----------------------------------------------------------------------------
// Interface stub for an AnimatedSystem. Basically any system that needs to
// be updated at a consistent interval.
//-----------------------------------------------------------------------------


#ifndef __ANIMATED_SYSTEM_H__
#define __ANIMATED_SYSTEM_H__

class AnimatedSystem
{
   public:
      virtual void update(int timeElapsed){}
};

#endif
