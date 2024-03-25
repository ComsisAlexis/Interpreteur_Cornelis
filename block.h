#ifndef __BLOCK_H
#define __BLOCK_H

#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "stack.h"

/*  @requires image2D a two-dimensional array of the image's pixels, tested a two-dimensional array representing
    the pixel already tested, x and y the coords of the pixel we are testing, init_color the color the pixel must
    be in order to be in the current block, *block_coords_x *block_coords_y the coordinates of the pixels of the 
    current block (may not be complete depending on the step the program is), *count the number of coords in 
    block_coords_x and block_coords_y, width and height the dimensions of the image;

    @assigns **tested *block_coords_x *block_coords_y, *count;

    @ensures fill recursively block_coords_x and block_coords_y with the coordinates of each pixel of the current block.
    *count represent the number of coordinates;

    TERMINAISON DE LA RECURSION :
    */
void exploration(pixel** image2D, int** tested, pixel init_color, int x, int y, int* block_coords_x, int* block_coords_y, int *count, int width, int height);


/*  @requires *s an intialised integer stack, *dir the current direction, *bord the current side, last_p the pixel 
    from the last block, current_p the current pixel, size_last_block the size of the last block;

    @assigns *s *dir *bord;

    @ensures do the right action based on the rules given depending on the difference of color and brightness between
    last_p and current_p;*/
void action(stack *s, enum Dir* dir, enum Bord* bord, pixel last_p, pixel current_p, int size_last_block, int debug_mode, int new_pixel_x, int new_pixel_y);


//  FRONTIER FUNCTIONS HAVE THE SAME @requires, @assigns, and @ensures
//  The only difference in requirements being that they are called respectivaly when the current direction is their direction.

/*  @requires image2D a two-dimensional array of the image's pixels, *x and *y the coords of the pixel we are testing,
    *block_coords_x *block_coords_y the coordinates of the pixels of the current block , count_coords the number of 
    coords in the current block, width and height the dimensions of the image, curr_bord the current side, 
    *new_pixel_x and *new_pixel_y used to store the coordinates of the next pixel;
    
    @assigns *pixel_x, *pixel_y, *x, *y, *new_pixel_x, *new_pixel_y
    
    @ensures *new_pixel_x and *new_pixel_y are the coordinates of the next pixel*/

void east_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords);

/*  @requires image2D a two-dimensional array of the image's pixels, *x and *y the coords of the pixel we are testing,
    *block_coords_x *block_coords_y the coordinates of the pixels of the current block , count_coords the number of 
    coords in the current block, width and height the dimensions of the image, curr_bord the current side, 
    *new_pixel_x and *new_pixel_y used to store the coordinates of the next pixel;
    
    @assigns *pixel_x, *pixel_y, *x, *y, *new_pixel_x, *new_pixel_y
    
    @ensures *new_pixel_x and *new_pixel_y are the coordinates of the next pixel*/
void south_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords);

/*  @requires image2D a two-dimensional array of the image's pixels, *x and *y the coords of the pixel we are testing,
    *block_coords_x *block_coords_y the coordinates of the pixels of the current block , count_coords the number of 
    coords in the current block, width and height the dimensions of the image, curr_bord the current side, 
    *new_pixel_x and *new_pixel_y used to store the coordinates of the next pixel;
    
    @assigns *pixel_x, *pixel_y, *x, *y, *new_pixel_x, *new_pixel_y
    
    @ensures *new_pixel_x and *new_pixel_y are the coordinates of the next pixel*/
void west_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords);

/*  @requires image2D a two-dimensional array of the image's pixels, *x and *y the coords of the pixel we are testing,
    *block_coords_x *block_coords_y the coordinates of the pixels of the current block , count_coords the number of 
    coords in the current block, width and height the dimensions of the image, curr_bord the current side, 
    *new_pixel_x and *new_pixel_y used to store the coordinates of the next pixel;
    
    @assigns *pixel_x, *pixel_y, *x, *y, *new_pixel_x, *new_pixel_y
    
    @ensures *new_pixel_x and *new_pixel_y are the coordinates of the next pixel*/
void north_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords);

/*  @requires **image2D a two-dimensional array of the image's pixels, *curr_x the current x position,
    *curr_y the current y position, *curr_dir the current direction, *curr_bord the current side, width
    and height the dimensions of the image, *attempts the number of attempts, *s a valid initialised
    stack, *direction_count a counter used to change either the side or the direction;

    @assigns *curr_x, *curr_y, *curr_dir, *curr_bord, *s, *direction_count

    @ensures each time this function is called, it perform a step of the program
    */
void next_coords(pixel** image2D, int* curr_x, int* curr_y, enum Dir* curr_dir, enum Bord* curr_bord, int width, int height, int* attempts, stack* s, int* direction_count, int debug_mode);


#endif