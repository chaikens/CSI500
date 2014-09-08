#ifndef __Proj1_h__ 
#define __Proj1_h__

struct program {
  char *filename;
  int n_times_used;
  struct program *next;
};

extern struct program program_list_head;

/*Public functions defined in Proj1ListUtils.h*/
struct program *find_nth_node( struct program *list, int n );
void print_list(struct program *list);
void append_program_name( struct program *list, char *name);

#endif /*__Proj1_h__*/
