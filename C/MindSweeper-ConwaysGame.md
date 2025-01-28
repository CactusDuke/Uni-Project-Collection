[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/b4vRliNg)
# Lab 4 - Pointers

This lab is due on **Sunday October 20, 2024 at 23:59 MDT**.

Submit what you have to GitHub classroom by pushing to your assignment repository.

Make sure your code is named as instructed, in the `src` folder, on the main branch.

Note that GitHub Classroom's due date is in UTC time zone, not MDT.

## Intro
Following your work with the fractal group, you decide to start a programming group of your own. You and all the members are interested in game development and decide to recreate some classic computer board games before going onto developing your own computer games. There are two games in particular you're all interested in: Minesweeper, and Conway's Game of Life.

## Rules

### Array Subscripting

Since this lab is about practicing working with pointers, you must use pointer arithmetic when accessing arrays. That means that you are **not** to use the subscripting operators `[]` for array indexing/subscripting at any point during either part of this lab. However, it is allowed to use them to declare arrays (either as local variables or function parameters).

```C
// Okay
int arr[2];
void foo(int (*arr)[]);

// Not okay
arr[0] = 1;
printf("%d\n", arr[1]);
```

### Provided Code

Both exercises will provide you with function prototypes for you to implement. These prototypes will be in a header file located inside the source directory `src` and should be included at the top of your source file as follows:

```C
// ex4qX.c
#include "ex4qX.h"

// Rest of the file ...
```
Where `X` is the exercise number.

Note that like previous labs, you will still have to create the source files yourself.

**IMPORTANT**: **Do not change the provided header files** as the given function prototypes will be used for testing your submission. You only need to implement the functions in your source files. You may however (and are encouraged to) implement your own functions as long as you do not change the header file.

### Header Files

You may not import any external libraries other than what is supplied in the provided header files. The needed libraries (`stdio` and `stdlib`) are provided in the header files.

# Part 1 - Minesweeper Board Generator

## Introduction

Minesweeper is a classic computer game composed of a grid and randomly hidden mines. The objective of the game is to find all the mines by following simple clues. These clues are numbers positioned on the grid representing the number of mines in the 8 neighbouring cells. Clicking on/sweeping a cell will either reveal a number, or a mine. Revealing a mine results in losing the game. The game is won once every cell without a mine has been sweeped.

Some members of your group have already created a program that generates a grid with randomly positioned mines. You're tasked with taking this incomplete board as input, and inserting the numbers where they should correctly be placed.

## Implementation

In `ex4q1.h`, you're provided with one function prototype for you to implement in a new file `ex4q1.c`:

```C
void countMines(int w, int h, const int (*grid)[w], int r, int c, int *count);
```

This function takes as parameters the minesweeper `grid`, its dimensions `w`, `h` (for width and height), and the coordinates of a given cell `r`, `c` (for row and column).

Given this data, the function should calculate the number of mines in the $8$ neighbouring cells of the given cell `r`, `c` (there may be less than $8$ neighbouring cells). The function does not return a value directly but instead uses the pointer `count` to store the result.

## Input Specifications

The input will be given through file redirection:
1. The first line is two integers `<width> <height>`, representing the minesweeper board's dimensions (HINT: In a grid, there are `height` rows and `width` columns).
    - You can assume that this line contains exactly two integers.
    - These two values should be integers $>0$, anything else is invalid and your program should handle this by terminating with a non-zero exit code.
2. The rest of the lines are two integers each, representing the location of one mine in the grid. The positions are represented as `<row> <col>`.
    - You can assume that each line contains exactly two integers.
    - You can always assume that these coordinates are inside the grid bounds.
3. The last line will always be `-1`, denoting the end of the input.

## Output Specifications

Your program should output the final minesweeper board in the following format:
1. `X` Should denote a mine.
2. Numbers `1-8` should be used for the number hints.
3. Use a space character ` ` to denote a cell with no neighbouring mines.
4. Leave a space before and after the cell value.
5. Each cell should be bordered using `|` for the left and right sides, `---` for the top and bottom sides, and `+` for the corners.
6. The grid should be printed having the top left cell be on the $0^{\text{th}}$ row, and $0^{\text{th}}$ column. While having the bottom right cell be on the `height-1`$^{\text{th}}$ row, and the `width-1`$^{\text{th}}$ column.

Below are examples to get you more familiar with the input and output format:

## Example I/O

### Example 1

Input:
```
5 5
3 2
1 2
1 3
-1
```

Output:
```
+---+---+---+---+---+
|   | 1 | 2 | 2 | 1 |
+---+---+---+---+---+
|   | 1 | X | X | 1 |
+---+---+---+---+---+
|   | 2 | 3 | 3 | 1 |
+---+---+---+---+---+
|   | 1 | X | 1 |   |
+---+---+---+---+---+
|   | 1 | 1 | 1 |   |
+---+---+---+---+---+
```

### Example 2

Input:
```
9 9
1 2
2 4
3 2
4 2
4 3
4 8
5 2
6 4
7 3
7 5
-1
```

Output:
```
+---+---+---+---+---+---+---+---+---+
|   | 1 | 1 | 1 |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+
|   | 1 | X | 2 | 1 | 1 |   |   |   |
+---+---+---+---+---+---+---+---+---+
|   | 2 | 2 | 3 | X | 1 |   |   |   |
+---+---+---+---+---+---+---+---+---+
|   | 2 | X | 4 | 2 | 1 |   | 1 | 1 |
+---+---+---+---+---+---+---+---+---+
|   | 3 | X | X | 1 |   |   | 1 | X |
+---+---+---+---+---+---+---+---+---+
|   | 2 | X | 4 | 2 | 1 |   | 1 | 1 |
+---+---+---+---+---+---+---+---+---+
|   | 1 | 2 | 3 | X | 2 | 1 |   |   |
+---+---+---+---+---+---+---+---+---+
|   |   | 1 | X | 3 | X | 1 |   |   |
+---+---+---+---+---+---+---+---+---+
|   |   | 1 | 1 | 2 | 1 | 1 |   |   |
+---+---+---+---+---+---+---+---+---+
```

### Example 3

Input:
```
15 15
-1
```

Output:
```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
```



# Part 2 - Conway's Game of Life

## Overview

Conway's Game of Life is composed of a 2D grid where each cell is either alive or dead. Conway's game of life is a *zero-player game*, as it proceeds deterministically from an initial state. The board's state evolves as time passes where each generation is determined by its previous one according to four simple rules:
1. Live cells with less than two live neighbours will die.
2. Live cells with more than three live neighbours will die.
3. Live cells with two or three live neighbours will remain alive.
4. Dead cells with exactly three live neighbours will gain life.

Your task for this lab is to simulate Conway's Game of Life given an initial set of live cells.

Much research has gone into this seemingly simple process, so we encourage you to learn more about it. The beauty of the game is that some arrangements of cells will go live in a stable cycle, some arragements will quickly die off, and some arragements will chaotically evolve before dying off.

## Implementation

While in theory, the grid should expand infinitely in all directions, we know that it is impossible for a computer simulation to do that. To handle this, we will use grid wrapping, meaning that the grid wraps around itself horizontally and vertically (known as a toroidal grid).

In `ex4q2.h`, you're provided with two function prototypes for you to implement in a new file `ex4q2.c`:

You will begin by implementing the function
```C
void nextCellState(int w, int h, const int (*grid)[w], int r, int c, int *state);
```
This function takes as parameters the grid, its dimensions `w`, `h` (for width and height), and the coordinates of a given cell `r`, `c` (for row and column).

Given this data, the function should calculate the next state of the given cell. The function does not return a value directly but instead uses the pointer `state` to store the result. The value pointed to by state should be set to `1` if the cell lives in the next generation, or `0` if it dies.

Next, you will implement
```C
void nextGeneration(int w, int h, int (*grid)[w]);
```
which will update the game grid in-place. Note that while the update to the 2D array happens in-place, in the Game of Life all cells are updated simultaneously. Make sure to account for this when checking if a cell should be dead or alive in the next step.

## Input Specifications

The input will be given through file redirection:
1. The first line is three integers `<width> <height> <generations>` where `width, height` are the grid dimensions, and `generations` is the number of generations to be simulated (not including the initial grid state).
    - You can assume that this line contains exactly three integers.
    - These three values should be integers $>0$, anything else is invalid and your program should handle this by terminating with a non-zero exit code.
2. The rest of the lines will be two integers each, each representing the position of an initially live cell formatted as `<row> <column>`.
    - You can assume that each line contains exactly two integers.
    - You can always assume that these coordinates are inside the grid bounds.
3. The last line will always be `-1`, denoting the end of the input.

## Output Specifications

Your program should output the grid state at generation `generations` (given from input) using the following format:
1. Print a space character ` ` for dead cells and `#` for live cells.
2. The grid should be printed having the top left cell be on the $0^{\text{th}}$ row, and $0^{\text{th}}$ column. While having the bottom right cell be on the `height-1`$^{\text{th}}$ row, and the `width-1`$^{\text{th}}$ column.

Below are examples to get you more familiar with the input and output format:

## Example I/O

### Example 1

Input:
```
20 20 10
9 10
11 10
10 11
11 11
10 12
-1
```

Output:
```
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
            # #     
             ##     
             #      
                    
                    
                    
                    
                    
```

### Example 2

Input:
```
40 12 100
3 4
3 5
3 6
3 8
3 9
4 3
4 4
4 5
4 10
4 12
5 1
5 2
5 4
5 9
5 12
6 1
6 2
6 4
6 9
6 12
7 3
7 4
7 5
7 10
7 12
8 4
8 5
8 6
8 8
8 9
-1
```

Output:
```
                                        
                                        
                                        
              ### ##                    
             ###    # #                 
           ## #    #  #                 
           ## #    #  #                 
             ###    # #                 
              ### ##                    
                                        
                                        
                                        
```

### Example 3

Input:
```
20 8 65
2 4
2 5
2 6
2 7
3 3
3 7
4 7
5 3
5 6 
-1
```

Output:
```
                    
                 ## 
                ####
#               ## #
                  ##
                    
                    
                    
```

## Checking

As always: You are provided with a script that checks your program named `check.sh`, this script will compare both your program's outputs to the expected outputs. To pass `check.sh`, your program's output should be an exact match to the expected output for all inputs given. All of the test cases that `check.sh` takes into account are provided in the `Testcases` directory.

In order to run this script first run this command to grant it proper permissions:

`chmod 700 check.sh`

Then to run the script run the command:

`./check.sh`

Read the output for more details should you fail any test cases or fail compilation.

**You are guaranteed a 50% minimum on this lab if you pass this script.**

Important: Make sure all your source code is inside of the source directory `src` and all files are named appropriately (`exAq1.c`, `exAq2.c`, etc. where `A` is the lab number).

