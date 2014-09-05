#include "csapp.h"
#include "Proj1.h"

static struct program *last_node( struct program *list )
{
  while( list->next != NULL ) {
    list = list->next;
  }
  return list;
}

static void append_node( struct program *list, struct program *node )
{
  struct program *where = last_node( list );
  node->next = NULL;  /*The added node will be at the end of the list.*/
  where->next = node;
}

void append_program_name( struct program *list, char *name )
{
  int len = strlen(name);
  char *string =  Malloc( len + 1 ); /*strlen does NOT count the '\0' terminator!*/
  struct program *node = Malloc( sizeof( struct program ) );
  strcpy( string, name );
  node->n_times_used = 1; /* We are using it the first time.*/
  node->filename = string;
  append_node( list, node );
}

struct program *find_nth_node( struct program *list, int n )
{
  while( n > 0 && list != NULL ) {
    list = list->next;
    n = n - 1;
  }
  return list;
}

void print_list(struct program *list){
  int i = 0;
  while( list->next != NULL )
    {
      i = i + 1;
      list = list->next;
      printf("%d %s (Used %d times.)\n", 
	     i, list->filename, list->n_times_used);
    }
}
