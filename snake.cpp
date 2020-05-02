#include "snake.h"
#include <csignal>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

WINDOW *win = NULL;
unsigned int speed = 100;
/* ------------------------------------------------------------------------- */
void create_border(void);
/* ------------------------------------------------------------------------- */

void sigterm_handler(int signum){
  echo();
  delwin(win);
  endwin();
  printf("\n\nSIGTERM Called\n");
  printf("\n\nI died gracefully\n");
  exit(signum);
}

void sigabrt_handler(int signum){
  echo();
  delwin(win);
  endwin();
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
  getch();

  /*Initialize screen*/
  win = initscr();
  noecho();
  if(win == NULL){
    fprintf(stderr,"\nError - initscr(): %d\n", ERR);
    echo();
    endwin();
    return 0;
  }

  refresh();

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


  /* ---------------------------------- */
  /*   THE GAME    */

  snake s;
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  cbreak();
  curs_set(0);

  for(; ;){
  input = false;
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
         ch != 27)
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
      else if(ch == 27);
    }

    if(input == true && ch == 27)
      break;

    if(input == false)
        s.mov();

    input = false;
    s.erase_snake();
    
  }

  /* ------------------------------------*/

  
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

void create_border(void){
  if(wborder(win, 0, 0, 0, 0, 0, 0, 0, 0) != OK){
    fprintf(stderr,"\nError wborder(): %d\n", ERR);
    delwin(win);
    echo();
    endwin();
    exit(0);
  }
}

/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
