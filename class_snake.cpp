#include "snake.h"
#include <stdlib.h>
#include <ctime>
#include <csignal>
#include <ncurses.h>
#include <unistd.h>

/* Constructor */
/* Giving initial values to render a snake */
snake::snake(void){
  this->create_new_ptr();
  this->head = tail = temp;
  this->head->x = 43;
  this->head->y = 12;
  this->head->direction = 0;
  this->head->no_of_blocks = 10;
  this->head->next = NULL;
  this->food_x = 4;
  this->food_y = 4;
  this->food_eat = true;
  this->score = 0;
  if(speed == 100)
    this->score_add = 2;
  else if(speed == 75)
    this->score_add = 5;
  else if(speed == 50)
    this->score_add = 10;
}

/* ------------------------------------------------------------------------- */

/* Creates a new segment at run time */
void snake::create_new_ptr(void){
  this->temp = NULL;
  this->temp = new body;
  if(this->temp == NULL){
    printf("\nERROR - snake::create_new_ptr()\n\n");
    delwin(win);
    echo();
    endwin();
    exit(0);
  }

  this->temp->x = -1;
  this->temp->y = -1;
  this->temp->no_of_blocks = -1;
  this->temp->direction = -1;
  this->temp->next = NULL;
  return;
}

/* ------------------------------------------------------------------------- */

/* Determines the next x coordinate of head on the basis of direction */
unsigned short snake::moved_position_of_head_x(unsigned short d/*direction*/){
  unsigned short res;
  if(d == 0){
    res = (this->head->x)+1;
    if(res > MAX_COL)
      res = MIN_COL;
  }

  else if(d == 1){
    res = (this->head->x)-1;
    if(res < MIN_COL)
      res = MAX_COL;
    }

  else res = head->x;
  return res;
}

/* ------------------------------------------------------------------------- */

/* Determines the next y coordinate of head on the basis of direction */
unsigned short snake::moved_position_of_head_y(unsigned short d/*direction*/){
  unsigned short res;
  if(d == 2){
    res = (this->head->y)-1;
    if(res < MIN_ROW)
      res = MAX_ROW;
  }

  else if(d == 3){
    res = (this->head->y)+1;
    if(res > MAX_ROW)
      res = MIN_COL;
  }

  else res = head->y;
  return res;
}

/* ------------------------------------------------------------------------- */

/* Add a new segement to snake body */
void snake::push(unsigned short d){
  this->create_new_ptr();
  this->temp->x = moved_position_of_head_x(d);
  this->temp->y = moved_position_of_head_y(d);

  this->temp->no_of_blocks = 1;
  this->temp->direction = d;
  this->head->next = temp;
  this->head = temp;
  this->temp = NULL;
  (this->tail->no_of_blocks)-=1;
  if(this->tail->no_of_blocks == 0)
    this->pop();
}

/* ------------------------------------------------------------------------- */

/* Delete a segment from snake body */
void snake::pop(void){
  if(this->tail == NULL){
    //error("underflow");
    return;
  }
  this->temp = this->tail;
  this->tail = this->tail->next;
  delete[] temp;
  temp = NULL;
  return;
}

/* ------------------------------------------------------------------------- */

/* erase the last step of snake, for animation */
/*
t=0ms   :  0000000H
t=100ms :   0000000H
t=200ms :    0000000H

In this case of snake moving from left to right,
As we see to make the snake look like moving forward, we print whole segment
at increased postion and the last '0' is replaced by white space.

*/
void snake::erase_snake(void){
  mvwprintw(win, this->erase_y , this->erase_x, " ");
}

/* ------------------------------------------------------------------------- */

void snake::mov(void){
  this->head->x = moved_position_of_head_x(this->head->direction);
  this->head->y = moved_position_of_head_y(this->head->direction);

  (this->head->no_of_blocks)++;
  (this->tail->no_of_blocks)--;

  if(this->tail->no_of_blocks <0)
    return;

  if(this->tail->no_of_blocks == 0)  //if the segment size is zero, it should be eliminated
    this->pop();
}

/* ------------------------------------------------------------------------- */

void snake::print(void){
  body *travel;
  unsigned short i,j;

  mvwprintw(win, this->head->y , this->head->x, "%c", hd);

  travel = this->tail;

  while(travel != NULL){
    if(travel->direction == 0){
      for(i=(travel->x)-1, j=0 ; j<travel->no_of_blocks ; j++, i--){
        if(i < MIN_COL)
          i = MAX_COL;
        mvwprintw(win, travel->y, i, "%c", bod);
       }

      if(travel == this->tail){
        this->erase_x = (++i);
        this->erase_y = travel->y;
      }
    }

    else if(travel->direction == 1){
      for(i=(travel->x)+1, j=0 ; j<travel->no_of_blocks ; j++, i++){
        if(i > MAX_COL)
          i = MIN_COL;
        mvwprintw(win, travel->y, i, "%c", bod);
      }

      if(travel == this->tail){
        this->erase_x = (--i);
        this->erase_y = travel->y;
      }
    }

    else if(travel->direction == 2){
      for(i=(travel->y)+1, j=0 ; j<travel->no_of_blocks ; j++, i++){
        if(i > MAX_ROW)
           i = MIN_ROW;
        mvwprintw(win, i, travel->x, "%c", bod);
      }

      if(travel == this->tail){
        this->erase_x = travel->x;
        this->erase_y = (--i);
      }
    }

    else if(travel->direction == 3){
      for(i=(travel->y)-1, j=0 ; j<travel->no_of_blocks ; j++, i--){
        if(i < MIN_ROW)
          i = MAX_ROW;
        mvwprintw(win, i, travel->x, "%c", bod);
      }

      if(travel == this->tail){
        this->erase_x = travel->x;
        this->erase_y = (++i);
      }
    }

    travel = travel->next;
  }

  this->erase_snake();

  if(this->food_eat == true){
    generate_food();
    food_eat = false;
  }

  mvwprintw(win, MAX_ROW+1, 30, "                  ");
  mvwprintw(win, MAX_ROW+1, 30, " SCORE : %lu ", this->score);
  mvwprintw(win, this->food_y, this->food_x, "%c", fod);

  if(mvwinch(win, this->head->y, this->head->x) == BOD){
    mvwprintw(win, 18, 32, "                ");
    mvwprintw(win, 19, 32, " YOU GOT KILLED ");
    mvwprintw(win, 20, 32, "                ");
    wrefresh(win);
    sleep(2);
    raise(SIGTERM);
  }

  if(this->food_x == this->head->x && this->food_y == this->head->y){
    this->head->x = moved_position_of_head_x(this->head->direction);
    this->head->y = moved_position_of_head_y(this->head->direction);

    (this->head->no_of_blocks)++;
    this->food_eat = true;
    this->score = this->score + this->score_add;
  }

}

/* ------------------------------------------------------------------------- */

bool snake::check_head_direction(unsigned short d){
          /*as body->direction tells about the direction of movement of a particular segment,
            we can check the movement of the head of the snake.*/
  if(this->head->direction == d)
    return true;

  else
    return false;
       }

/* ------------------------------------------------------------------------- */

void snake::generate_food(void){
  srand(time(NULL));
  while(true){
    this->food_x = ( rand()%(MAX_COL - MIN_COL + 1) ) + MIN_COL;
    this->food_y = ( rand()%(MAX_ROW - MIN_ROW + 1) ) + MIN_ROW;

    if(this->food_x == this->erase_x && this->food_y == this->erase_y)
      continue;

    if(mvwinch(win, this->food_y, this->food_x) != HD &&
       mvwinch(win, this->food_y, this->food_x) != BOD)
      break;
  }
}

/* ------------------------------------------------------------------------- */
