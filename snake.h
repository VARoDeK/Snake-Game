#include <ncurses.h>

/* Header file for Snake Program */
#ifndef __SNAKE_H__ /* SNAKE_H */

#define __SNAKE_H__

/* ------------------------------------------------------------------------- */
#define ROW_WIN 40        //max number of lines in a window
#define COL_WIN 80        //max number of characters in a window

#define MAX_ROW ROW_WIN-2  //max line no snake can go
#define MIN_ROW 1          //min line no snake can go
#define MAX_COL COL_WIN-2  //max character position snake can go
#define MIN_COL 1          //min character position snake can go

#define START_X 0
#define START_Y 0
#define HD 'H'
#define BOD 'o'
/* 
 * All the program files will be needing the variable 'win'. Using 'extern'
 * keyword we make sure that 'win' is just declared and not defined/
 * initialized. The definition is done in 'main.cpp' 
 */
extern WINDOW *win;

void create_border(void);
void start_menu(void);
void pause_menu(void);
void exit_menu(void);
/* ------------------------------------------------------------------------- */
/*
The snake body will be divided in different segments:
    ********
           *
           *
           *********H
-Suppose the image above is a snake, 'H' represents head.
-The snake will be printed in different segments.
     ******B
           *
           *
           A********H
- 8 blocks will be printed from 'H' in right-to-left direction.
- 3 blocks will be printed from 'A' in bottom-to-up direction.
- 6 blocks will be printed from 'B' in right-to-left direction.
*/

/* ------------------------------------------------------------------------- */

struct body
{
  unsigned short x,y;          //'x' and 'y' coordinate of starting of each segment.
  unsigned short direction;    //direction of movement of segment.
  unsigned short no_of_blocks; //no of blocks in each segment.
  body *next;
};
/*
Direction:
0 - segment moving towards right direction
  - segment printed from right-to-left
1 - segment moving towards left direction
  - segment printed from left-to-right
2 - segment moving towards upward direction
  - segment printed from up-to-bottom
3 - segment moving towards downward direction
  - segment printed from bottom-to-up
*/

/* ------------------------------------------------------------------------- */

class snake{
  private:
    body *head, *tail, *temp;
    const char hd = HD;
    const char bod = BOD;
    const char fod = '*';
//head- head segment of snake.
//tail- tail segment of snake.
/*
 * This is because during movement, the length of only head and tail segment
 * will change.
 */

  unsigned short erase_x, erase_y;
  unsigned short food_x, food_y;
  bool food_eat;
  unsigned long score;
  unsigned long score_add;
 //to erase the previous path of snake, so as to animate it.

  public:
    snake(void);
    void create_new_ptr(void);   //create a new memory-block dynamically and store the address in 'temp'.
    void push(unsigned short);            //push a memory-block to store info about new segment.
    void pop(void);              //deletes the memory-block.
    void erase_snake(void);      //erase the previous path of snake so as to animate it.
    void mov(void);              //creates a new path for snake so as snake should move.
    void print(void);            //prints the snake.
    unsigned short moved_position_of_head_x(unsigned short); //returns the moved 'x' coordinate of head.
    unsigned short moved_position_of_head_y(unsigned short); //returns the moved 'y' coordinate of head.
    bool check_head_direction(unsigned short);
    void generate_food(void);
};

#endif /* SNAKE_H */
