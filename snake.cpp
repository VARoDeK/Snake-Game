#include<windows.h>
#include<time.h>    //for clock_t used in delay()
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

/*-----------------------------------------------------------------------------------------------------------------------*/
/*--ADD THE CODES IN THIS BLOCK AS COMMENTS WHEN USING THIS CODE IN TURBO--*/
//-Block starts:
COORD coord={0,0};
void gotoxy(int,int);
void clrscr();
void delay(int);
void set_window_size();
void ShowConsoleCursor(bool);
//-Block ends
/*-----------------------------------------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------------------------------------*/
struct body
{
short x,y;        //'x' and 'y' coordinate of starting of each segment.
short direction;  //direction of movement of segment.
short no_of_blocks; //no of blocks in each segment.
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

/*-----------------------------------------------------------------------------------------------------------------------*/

//Boundaries of display window:
const short x_start_bound = 1;
const short x_end_bound = 80;
const short y_start_bound = 1;
const short y_end_bound = 25;
//----------------------------------
const char bod = '0';       //character to display body.
const char hd = 'H';        //character to display head.
unsigned int speed = 100;
/*-----------------------------------------------------------------------------------------------------------------------*/
class snake
{
 body *head, *tail, *temp;
 //head- head segment of snake.
 //tail- tail segment of snake.
 /*
   This is because during movement, the length of only head and tail segment will change.
  */
 short erase_x, erase_y;
 //to erase the previous path of snake, so as to animate it.

  public:
      snake() //constructor to define snake for NEW GAME
      {
       create_new_ptr();
       if(temp == NULL)
       {
       //  error("Could not Allocate Memory For New Body Segment");
        return;
        }
       head = tail = temp;
       head->x = 43;
       head->y = 12;
       head->direction = 0;
       head->no_of_blocks = 50;
       head->next == NULL;
       }


      bool check_head_direction(short d)
      {
          /*as body->direction tells about the direction of movement of a particular segment,
            we can check the movement of the head of the snake.*/
       if(head->direction == d)
        return true;

        else
         return false;
       }

void create_new_ptr(void);   //create a new memory-block dynamically.
void push(short);            //push a memory-block to store info about new segment.
void pop(void);              //deletes the memory-block.
void erase_snake(void);      //erase the previous path of snake so as to animate it.
void mov(void);              //creates a new path for snake so as snake should move.
void print(void);            //prints the snake.
short moved_position_of_head_x(short); //returns the moved 'x' coordinate of head.
short moved_position_of_head_y(short); //returns the moved 'y' coordinate of head.
};

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

int main()
{
 snake s; //snake created
 char ch;
 int i;
 unsigned short input = 0;
 set_window_size();       //to be deleted if using this code in TURBO
 ShowConsoleCursor(false);    //to be deleted if using this code in TURBO
/*s.print();
getch();
s.mov();
s.erase_snake();
s.print();*/
 for( ; ; )
 {
  input = 0;
  s.print();
  for(i=0; i<speed && input==0; i+=10)
  {
   if(kbhit())
   {
    ch = getch();
    input = 1;
 /* 77- move right
    75 - move left
    72 - move up
    80 - move down*/
    if(ch == 77 && !s.check_head_direction(0) && !s.check_head_direction(1))
     s.push(0);
    else if(ch == 75 && !s.check_head_direction(1) && !s.check_head_direction(0))
     s.push(1);
    else if(ch == 72 && !s.check_head_direction(2) && !s.check_head_direction(3))
     s.push(2);
    else if(ch == 80 && !s.check_head_direction(3) && !s.check_head_direction(2))
     s.push(3);

    else if(ch == 27)
      getch();
    else
     input = 0;
    }
    delay(10);
   }

    if(input == 0)
        s.mov();
//if no input has been made to move turn the direction of the snake, it should move in normal way.

   s.erase_snake();
  }


 return 0;
 }










/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
      void snake::create_new_ptr(void)
      {
       temp = NULL;
       temp = new body;
        if(temp == NULL)
          return;
       temp->x = -1;
       temp->y = -1;
       temp->no_of_blocks = -1;
       temp->direction = -1;
       temp->next = NULL;
         return;
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
     short snake::moved_position_of_head_x(short d/*direction*/)
     {
      short res;
      if(d == 0)
      {
       res = (head->x)+1;
       if(res == x_end_bound)
         res = x_start_bound + 1;
       }


      else if(d == 1)
      {
       res = (head->x)-1;
       if(res == x_start_bound)
         res = x_end_bound - 1;
       }

       else res = head->x;
     return res;
     }

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
     short snake::moved_position_of_head_y(short d/*direction*/)
     {
      short res;
      if(d == 2)
      {
       res = (head->y)-1;
       if(res == y_start_bound)
         res = y_end_bound - 1;
       }


      else if(d == 3)
      {
       res = (head->y)+1;
       if(res == y_end_bound)
         res = y_start_bound + 1;
       }

      else res = head->y;
     return res;
     }



/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

      void snake::push(short d)
      {
       create_new_ptr();
       if(temp == NULL)
       {
         printf("Could not Allocate Memory For New Body Segment");
        return;
        }

       temp->x = moved_position_of_head_x(d);
       temp->y = moved_position_of_head_y(d);

       temp->no_of_blocks = 1;
       temp->direction = d;
       head->next = temp;
       head = temp;
       temp = NULL;
       (tail->no_of_blocks)-=1;
        if(tail->no_of_blocks == 0)
         pop();
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
      void snake::pop(void)
      {
          if(tail == NULL)
          {
           //error("underflow");
            return;
           }
       temp = tail;
       tail = tail->next;
       delete temp;
       temp = NULL;
        return;
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
      void snake::erase_snake(void)
      {
       gotoxy(erase_x , erase_y);
       printf(" ");
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
      void snake::mov(void)
      {
       head->x = moved_position_of_head_x(head->direction);
       head->y = moved_position_of_head_y(head->direction);

       (head->no_of_blocks)++;
       (tail->no_of_blocks)--;

       if(tail->no_of_blocks <0)
        exit(0);

       if(tail->no_of_blocks == 0)  //if the segment size is zero, it should be eliminated
        pop();
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
      void snake::print(void)
      {
       body *travel;
       short i,j;

       gotoxy(head->x , head->y);
       printf("%c", hd);

       travel = tail;

       while(travel != NULL)
       {
        if(travel->direction == 0)
        {
         for(i=(travel->x)-1, j=0 ; j<travel->no_of_blocks ; j++, i--)
         {
          if(i == x_start_bound)
           i = x_end_bound - 1;
          gotoxy(i, travel->y);
          printf("%c" , bod);
          }
         if(travel == tail)
         {
          erase_x = ++i;
          erase_y = travel->y;
          }
         }


        else if(travel->direction == 1)
        {
         for(i=(travel->x)+1, j=0 ; j<travel->no_of_blocks ; j++, i++)
         {
          if(i == x_end_bound)
           i = x_start_bound + 1;
          gotoxy(i, travel->y);
          printf("%c" , bod);
          }
          if(travel == tail)
          {
           erase_x = --i;
           erase_y = travel->y;
          }
         }


        else if(travel->direction == 2)
        {
         for(i=(travel->y)+1, j=0 ; j<travel->no_of_blocks ; j++, i++)
         {
          if(i == y_end_bound)
           i = y_start_bound + 1;
          gotoxy(travel->x , i);
          printf("%c" , bod);
          }
          if(travel == tail)
          {
           erase_x = travel->x;
           erase_y = --i;
          }
         }


        else if(travel->direction == 3)
        {
         for(i=(travel->y)-1, j=0 ; j<travel->no_of_blocks ; j++, i--)
         {
          if(i == y_start_bound)
           i = y_end_bound - 1;
          gotoxy(travel->x , i);
          printf("%c" , bod);
          }
          if(travel == tail)
          {
           erase_x = travel->x;
           erase_y = ++i;
           }
         }

         travel = travel->next;
        }
       }
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
























/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*--ADD THE CODES IN THIS BLOCK AS COMMENTS WHEN USING THIS CODE IN TURBO--*/
//Block Starts
void gotoxy(int x, int y)
{
 coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

 void set_window_size()
 {
  system("mode 81,26");
  SMALL_RECT WinRect = {0,0,81,26};
  SMALL_RECT* WinSize =&WinRect;
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),true, WinSize);
  }

void clrscr()
 {
  system("cls");
  }


void delay(int x)
{
 clock_t goal=x+clock();
 while(goal>clock());
 }

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


 //Block ends
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


