/* Header file for Snake Program */
#ifndef __SNAKE_H__ /* SNAKE_H */

#define __SNAKE_H__

/* ------------------------------------------------------------------------- */
#define ROW_WIN 40        //max height of window
#define COL_WIN 80        //max width of window

#define MAX_ROW ROW_WIN-1  //max distance (height) snake can go
#define MIN_ROW 1          //min distance (height) snake can go
#define MAX_COL COL_WIN-1  //max distance (width) snake can go
#define MIN_COl 1          //min distance (width) snake can go

#define START_X 0
#define START_Y 0

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
//head- head segment of snake.
//tail- tail segment of snake.
/*
 * This is because during movement, the length of only head and tail segment
 * will change.
 */

  unsigned short erase_x, erase_y;
 //to erase the previous path of snake, so as to animate it.

  public:
    snake();
    void create_new_ptr(void);   //create a new memory-block dynamically and store the address in 'temp'.
    void push(short);            //push a memory-block to store info about new segment.
    void pop(void);              //deletes the memory-block.
    void erase_snake(void);      //erase the previous path of snake so as to animate it.
    void mov(void);              //creates a new path for snake so as snake should move.
    void print(void);            //prints the snake.
    short moved_position_of_head_x(short); //returns the moved 'x' coordinate of head.
    short moved_position_of_head_y(short); //returns the moved 'y' coordinate of head.
};

#endif /* SNAKE_H */
