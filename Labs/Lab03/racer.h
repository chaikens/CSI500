#define nLoops 20000000

#ifdef CONFIG_VOLATILE 
volatile
#endif 
int sharedInt;
/* ring has static lifetime.
   ring is initialized in racer.c
   All the new threads run racer so
   they all share ring.
*/

void * racer( void * arg );

