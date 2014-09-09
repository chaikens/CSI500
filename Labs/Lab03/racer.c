#include "racer.h"

#ifdef CONFIG_VOLATILE 
volatile
#endif
int sharedInt = 0;

void  * racer(void *tid)
{
  int count;
  for(count = nLoops; count > 0; count--)
    {
      sharedInt = sharedInt + 1;
    }
}
