#include "snake.h"
#include <ncurses.h>
#include <stdlib.h>

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

