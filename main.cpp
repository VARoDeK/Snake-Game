#include "snake.h"
#include <csignal>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

WINDOW *win = NULL;
unsigned int speed = 100;

/* ------------------------------------------------------------------------- */

/* Handle the program if it is terminated using kill(), pkill() or 'ctrl+C' */
void sigterm_handler(int signum){
  echo();          //enable ncurses echo
  curs_set(1);
  delwin(win);     //delete window created for game
  endwin();        //end intitial window
  printf("\n\nSIGTERM Called\n");
  printf("\n\nI died gracefully\n");
  exit(signum);
}

void sigabrt_handler(int signum){
  echo();          //enable ncurses echo
  curs_set(1);
  delwin(win);     //delete window created for game
  endwin();        //end initial window
  printf("\n\nSIGABRT Called\n");
  printf("\n\nI died gracefully\n");
  exit(signum);
}
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
int main(){
  win = NULL;
  bool input = false;
  wchar_t ch;
  unsigned int i;

  signal(SIGABRT, sigabrt_handler);
  printf("\nREGISTERED SIGABRT HANDLER\n");
  signal(SIGTERM, sigterm_handler);
  printf("REGISTERED SIGTERM HANDLER\n");

  printf("Press any key..");
  usleep(500000);
  getch();


  /*Initialize screen*/
  win = initscr();
  
  noecho(); //do not echo during ncurses getch()

  if(win == NULL){
    fprintf(stderr,"\nError - initscr(): %d\n", ERR);
    echo();
    endwin();
    return 0;
  }

  refresh(); //render the initial screen

  /*Make new Window*/
  win = newwin(ROW_WIN, COL_WIN, START_X, START_Y);
  if(win == NULL){
    fprintf(stderr,"\nError - WINDOW *win: %d\n", ERR);
    echo();
    endwin();
    return 0; 
  }

  create_border();
  wrefresh(win);
  
  /* Make the cursor invisible */
  curs_set(0);

  start_menu();

  /* ---------------------------------- */
  /*   THE GAME    */

  snake s;

  /* Do not wait during getch() if user does not give any input */
  nodelay(stdscr, TRUE);

  /* Detect UP, DOWN, LEFt, RIGHT arrow keys */
  keypad(stdscr, TRUE);

  cbreak();

  for(; ;){
  input = false;

  /* Print the snake */
  s.print();
  wrefresh(win);

    for(i=0; i<speed && input==false; i+=10){
      usleep(10000);
      ch=0;
      ch = getch();
      if(ch != KEY_UP &&
         ch != KEY_DOWN &&
         ch != KEY_LEFT &&
         ch != KEY_RIGHT &&
         ch != 27 &&
         ch != 32)
      continue;

      input = true;
      if(ch == KEY_RIGHT && !s.check_head_direction(0) && !s.check_head_direction(1))
        s.push(0);
      else if(ch == KEY_LEFT && !s.check_head_direction(1) && !s.check_head_direction(0))
        s.push(1);
      else if(ch == KEY_UP && !s.check_head_direction(2) && !s.check_head_direction(3))
        s.push(2);
      else if(ch == KEY_DOWN && !s.check_head_direction(3) && !s.check_head_direction(2))
        s.push(3);
      else if(ch == 32)
        pause_menu();
      else if(ch == 27)
        exit_menu();
    }

    if(input == false)
      s.mov();

  }

  /* ------------------------------------*/

  /* Get things back to normal */
  nodelay(stdscr, FALSE);
  keypad(stdscr, FALSE);
  curs_set(1);
  getch();

  delwin(win);
  echo();
  endwin();
  return 0;
}

/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
