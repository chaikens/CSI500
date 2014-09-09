#define nLoops 20000000

#ifdef CONFIG_VOLATILE 
volatile
#endif 
int sharedInt;
/* sharedInt has static lifetime.
   sharedInt is initialized in racer.c
   All the new threads run racer so
   they all share sharedInt.
*/

void * racer( void * arg );

