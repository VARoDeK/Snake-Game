#include "snake.h"
#include <csignal>
#include <ncurses.h>

extern unsigned int speed;

/* ------------------------------------------------------------------------- */

void start_menu(void){
  wchar_t ch;

  wclear(win);
  create_border();
  wrefresh(win);
  nodelay(stdscr, FALSE);
  noecho();
  mvwprintw(win, 5, 30, "WELCOME TO SNAKE!!");
  mvwprintw(win, 8, 3, "A re-implementation of 1976 arcade game Blockade "
                       "using only Linked Lists.");
  mvwprintw(win, 9, 10, "Follow the project : https://github.com/VARoDeK/Snake-Game");
  mvwprintw(win, 14, 20, "Please select snake speed.");
  mvwprintw(win, 15, 28, "Press 1 for Slow.");
  mvwprintw(win, 16, 28, "Press 2 for Medium.");
  mvwprintw(win, 17, 28, "Press 3 for Fast");
  mvwprintw(win, 18, 28, "Press Esc to Exit");

  mvwprintw(win, 31, 4, "INSTRSUCTIONS:");
  mvwprintw(win, 32, 4, "1) - Press SPACE key during game to pause.");
  mvwprintw(win, 33, 4, "1) - Press Esc key during game to exit.");

  wrefresh(win);

  ch = 0;

  while(ch==0){
    ch = getch();
    if(ch == '1')
      speed = 100;
    else if(ch == '2')
      speed = 75;
    else if(ch == '3')
      speed = 50;
    else if(ch == 27)
      raise(SIGTERM);
    else{
      mvwprintw(win, 21, 12, "Please select correct Option.");
      wrefresh(win);
      ch = 0;
      continue;
    }
  }

  wclear(win);
  create_border();
  wrefresh(win);

  return; 
}

/* ------------------------------------------------------------------------- */

void pause_menu(void){
  wchar_t ch;
  
  nodelay(stdscr, FALSE);

  mvwprintw(win, 18, 28, "                       ");
  mvwprintw(win, 19, 33, " GAME PAUSED ");
  mvwprintw(win, 20, 28, " PRESS SPACE TO RESUME ");
  mvwprintw(win, 21, 28, "                       ");
  wrefresh(win);
 
  ch=0;
  while(ch == 0){
    ch = getch();
    if(ch != 32)
      ch=0;
  }

  nodelay(stdscr, TRUE);
  wclear(win);
  create_border();
  wrefresh(win);

  return;
}
/* ------------------------------------------------------------------------- */

void exit_menu(void){

  wchar_t ch;
  
  nodelay(stdscr, FALSE);

  mvwprintw(win, 18, 28, "                       ");
  mvwprintw(win, 19, 30, " YOU WANT TO EXIT? ");
  mvwprintw(win, 20, 29, " PRESS ESC TO RESUME ");
  mvwprintw(win, 21, 31, " PRESS Q TO quit ");
  mvwprintw(win, 22, 28, "                       ");
  wrefresh(win);
 
  ch=0;
  while(ch == 0){
    ch = getch();
    if(ch == 27)
      break;
    else if(ch=='Q' || ch=='q')
      raise(SIGTERM);
    else
      ch=0;
  }

  nodelay(stdscr, TRUE);
  wclear(win);
  create_border();
  wrefresh(win);

  return;
}

/* ------------------------------------------------------------------------- */
