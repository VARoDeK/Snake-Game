# Snake-Game/ Snake

> Snake is the common name for a video game concept where the player maneuvers a line which grows in length, with the line itself being a primary obstacle. The concept originated in the 1976 arcade game Blockade, and the ease of implementing Snake has led to hundreds of versions (some of which have the word snake or worm in the title) for many platforms. After a variant was preloaded on Nokia mobile phones in 1998, there was a resurgence of interest in the snake concept as it found a larger audience. 

> APA - Wikipedia contributors. (2020, March 30). Snake (video game genre). In Wikipedia, The Free Encyclopedia. Retrieved
> 11:00, May 2, 2020

> , from https://en.wikipedia.org/w/index.php?title=Snake_(video_game_genre)&oldid=948244431

---

# Implementation

Purely implemented using STL and Linked Lists.

---

# Successfully builds on:

- [x] Arch Linux
- [x] MacOS

---

# How to run project?

__Make sure that `ncurses` library is installed on your system.__

1) Clone the Repository
2) Switch to `master` branch
3) To build the project, enter `make` .
4) Run `./snake` .
5) To remove the program compiled in step 3, enter `make clean`.

---

# Project Tree

1) `snake.h` - Contains all the function and variables declaration which are used by all the files. It also contains:
    * `struct body` - The body segment of snake.
    * `class snake` - A whole single snake.
  
2) `class_snake.cpp` - Contains definitions of functions of `class snake`.

3) `functions.cpp` - Contains definitions of functions used in `main.cpp`. Those functions are either declared in `main.cpp` or `snake.h`.

4) `main.cpp` - The actual logic of forming window, signal handling, printing, etc, is written here.

---

# How snake works?

The division of snake body into segments is explained in `snake.h`.

Now let's assume __b<sub>n</sub>__ means __n<sup>th</sup>__ body segment. Then linked list of snake, with 2 body segments, looks like:

__tail ----> b<sub>2</sub> ----> b<sub>1</sub> ----> head__ 

The printing starts from tail and a new body segment is pushed from head side.

---
