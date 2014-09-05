#include "csapp.h"
#include "Proj1.h"

/*Declarations of private helper functions.
  You don't need them unless a function call is
  coded before the function definition.*/
static void print_menu();
static void run_program(char *c);
static void run_chosen_program(char *c);
static void add_program( );

/* The head of the program popularity list is 
   statically allocated and initialized at compile time.
   It is a DUMMY-HEAD! */
struct program program_list_head =
  {
    .filename = NULL,
    .n_times_used = 0,
    .next = NULL
  };
/*Huh? We used the new C syntax for initializing structure fields
  BY NAME instead of position!  This is used a lot in the Linux Kernel.*/

static void print_menu()
{
  printf("A Add a program.\n");
  printf("Q Quit.\n");
  print_list( &program_list_head );
  printf("What should the shell do now?:");
}

static char *parse_program_name(char *buf) {
  /*Derived from Bryant and O'Hallaron's argument parsing code.
    Optional for CSI500: save and use the arguments too.    */
  char *delim;         /* Points to first AND LATER space delimiters */
  int argc;            /* Number of args */
  char *name;
  /* Determining background vs foreground a different in CSI500 */

  buf[strlen(buf)-1] = ' ';     /* Replace trailing '\n' with space */
  while (*buf && (*buf == ' ')) /* Ignore leading spaces */
    buf++;
  name = buf;
  /* The original code built the argv list here.*/
  argc = 0;
  while ((delim = strchr(buf, ' '))) {
    /*If you wanted to save the argument locations, do that here.*/
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' ')) /* Ignore spaces */
      buf++;
    argc = argc + 1;
    }
  if (argc == 0)  /* Ignore blank line */
	return NULL;
  if (argc > 1)
    printf("Proj1 in CSI500 doesn't handle program arguments.\n"); 
  return name;
}

static int ask_user_yes(char *question)
{
#define ASK_YES_BUFFSIZE 3
  char answerline[ASK_YES_BUFFSIZE];
  /*We will loop until the user actually types a n or an y.*/
  while( 1 ) {
    printf(question);
    Fgets(answerline, ASK_YES_BUFFSIZE, stdin);
    /*Try to make Fgets copy in "y\n"  or "n\n",
      '\0' terminated strings.*/
    if( feof(stdin))
      exit(0);
    if( strcmp(answerline, "y\n") == 0 ) return 1;
    if( strcmp(answerline, "n\n") == 0 ) return 0;
    printf("You typed neither n nor y. Try again.\n"); 
  }
}

static void run_chosen_program(char *number_string)
{
  int n_chosen, sscanf_ret;
  struct program *nth_prog;
  sscanf_ret = sscanf(number_string, "%d", &n_chosen);
  if(sscanf_ret != 1 ) {
    printf("The shell couldn't parse a number. Try again.\n");
    return;
  }
  nth_prog = find_nth_node( &program_list_head, n_chosen );
  /* Part of CSI500's assignment is to INCREMENT the n_times_used count
     and REORDER THE LIST so more popular programs are offered earlier!
  */
  if(nth_prog != NULL ) {
    run_program( nth_prog->filename );
  }
  else {
    printf("That number is not in the menu! Try again.\n");
  }
}

static void run_program(char *c) {
  int must_wait = ask_user_yes("Wait for completion? Type y or n:");
  /*We will fork/exec and this function in the parent will either
    wait or return.  See the reading assignment!*/
    if( must_wait ) {
    /* DO SYSTEMS PROGRAMMING HERE! */
      printf("Proj1 hasn't been programmed yet to fork/exec and wait.\n");  
      return ;
    }
    else {
      /* DO SYSTEMS PROGRAMMING HERE! */
      printf("Proj1 hasn't been programmed yet to fork and exec in the background.\n");  
      return;
    }
}
  
static void add_program( ) {
  char progline[MAXLINE];
  char *delimloc;
  int good_program = 0;
  char *name;
  while( !good_program ) {
    printf("What program do you want to add and run?:");
    Fgets(progline,MAXLINE,stdin);
    if( feof(stdin))
      exit(0);
    name = parse_program_name(progline);
    if( name == NULL ) {
      printf("Just type a program's name and ENTER, no spaces or anything!\n");
      continue;
    }
    good_program = 1;
  }
  append_program_name( &program_list_head, name );
  run_program( name );
}

int main(int argc, char *argv[])
{
  char cmdline[MAXLINE];

  while( 1 ) {
    print_menu();
    Fgets(cmdline, MAXLINE, stdin);
    if( feof(stdin))
      exit(0);
    if( cmdline[0] == 'A' )
      add_program();
    else if ( cmdline[0] == 'Q' )
      exit( 0 );
    else run_chosen_program(cmdline);
  }
}
