#include "snake.h"
#include <csignal>
#include <ncurses.h>

/* ------------------------------------------------------------------------- */

void start_menu(void){
  wchar_t ch;

  wclear(win);
  create_border();
  wrefresh(win);
  nodelay(stdscr, FALSE);
  noecho();
  mvwprintw(win, 3, 30, "WELCOME TO SNAKE!!");
  mvwprintw(win, 5, 3, "A re-implementation of 1976 arcade game Blockade "
                       "using only Linked Lists.");
  mvwprintw(win, 6, 10, "Follow the project : https://github.com/VARoDeK/Snake-Game");
  mvwprintw(win, 10, 20, "Please select snake speed.");
  mvwprintw(win, 11, 28, "Press 1 for Slow.");
  mvwprintw(win, 12, 28, "Press 2 for Medium.");
  mvwprintw(win, 13, 28, "Press 3 for Fast");
  mvwprintw(win, 14, 28, "Press Esc to Exit");

  mvwprintw(win, 19, 4, "INSTRSUCTIONS:");
  mvwprintw(win, 20, 4, "1) - Use arrow keys to move snake.");
  mvwprintw(win, 21, 4, "2) - Press SPACE key during game to pause.");
  mvwprintw(win, 22, 4, "3) - Press Esc key during game to exit.");

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
      mvwprintw(win, 16, 25, "PLEASE SELECT CORRECT OPTION.");
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

  mvwprintw(win, 10, 28, "                       ");
  mvwprintw(win, 11, 33, " GAME PAUSED ");
  mvwprintw(win, 12, 28, " PRESS SPACE TO RESUME ");
  mvwprintw(win, 13, 28, "                       ");
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

  mvwprintw(win, 10, 28, "                       ");
  mvwprintw(win, 11, 30, " YOU WANT TO EXIT? ");
  mvwprintw(win, 12, 29, " PRESS ESC TO RESUME ");
  mvwprintw(win, 13, 31, " PRESS Q TO quit ");
  mvwprintw(win, 14, 28, "                       ");
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
