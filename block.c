#include "block.h"


void exploration(pixel** image2D, int** tested, pixel init_color, int x, int y, int* block_coords_x, int* block_coords_y, int *count, int width, int height) {
    tested[y][x] = 1; //we mark the pixel we are testing
    if (color_cmp(image2D[y][x], init_color)) { //if the pixel tested has the same color as the pixel that called exploration
        block_coords_x[*count] = x; //it is being added to the array of the current block
        block_coords_y[*count] = y; 
        *count += 1;

        //exploration is called recursively on the 4 pixels next to the one that we just tested but only if they have not been tested yet
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if ((i+j)*(i+j) == 1 && tested[(y+height+j)%height][(x+width+i)%width] == 0) { 
                    //i+j squarred = 1 is only true if the pixel are just next to the current one so we avoid diagonals
                    //that is the reason of this test 
                    exploration(image2D, tested, image2D[y][x], (x+width+i)%width, (y+height+j)%height, block_coords_x, block_coords_y, count, width, height); 
                }
            //in this code it is often written (x+width+i)%width and (y+height+j)%height. It is because the image is a torus (fr: Un tore)
            //that means that a pixel on the last column of pixel is a neighbor of a pixel from the first column
            //the same goes for lines.
            }
        }
    }
}

void action(stack *s, enum Dir* dir, enum Bord* bord, pixel last_p, pixel current_p, int size_last_block, int debug_mode, int new_pixel_x, int new_pixel_y) {
    
    //compute the difference of color and brightness
    int diff_color = pixel_diff_color(last_p, current_p);
    int diff_brightness = pixel_diff_brightness(last_p, current_p);

    //call the right operation on stack depending on the difference of color and brightness
    if (diff_brightness == 0) {
        if (diff_color == 1) {
            stack_plus(s);
        } else if (diff_color == 2) {
            stack_divide(s);
        } else if (diff_color == 3) {
            stack_greater(s);
        } else if (diff_color == 4) {
            stack_duplicate(s);
        } else if (diff_color == 5) {
            in_char(s);
        }
    } else if (diff_brightness == 1) {
        if (diff_color == 0) {
            stack_size_add(s, size_last_block);
        } else if (diff_color == 1) {
            stack_minus(s);
        } else if (diff_color == 2) {
            stack_remainder(s);
        } else if (diff_color == 3) {
            stack_turn(s, dir);
        } else if (diff_color == 4) {
            turn(s);
        } else if (diff_color == 5) {
            out_number(s);
        }
    } else if (diff_brightness == 2) {
        if (diff_color == 0) {
            if (s->current_size > 0) {
                stack_pop(s);
            }
        } else if (diff_color == 1) {
            stack_prod(s);
        } else if (diff_color == 2) {
            stack_not(s);
        } else if (diff_color == 3) {
            stack_side(s, bord);
        } else if (diff_color == 4) {
            in_number(s);
        } 
        else if (diff_color == 5) {
            out_char(s);
        }
    }
    if (debug_mode) {
        printf("----------------------------\n");
        stack_show(s);
        printf("current direction : %d, current side : %d\n", *dir, *bord);
        printf("coords x: %d y:%d \n", new_pixel_x, new_pixel_y);
        getc(stdin);
    }
}


void east_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords) {
    int x_max = 0;
    int y_min = height;
    int y_max = 0;
    for (int k = 0; k < count_coords; k++) {
            
        *x = block_coords_x[k];
        *y = block_coords_y[k];
            
        if (!color_cmp(image2D[*y][*x], image2D[*y][(*x+width+1)%width])) { //le pixel de droite n'a pas la meme couleur
            if (*x > x_max) { //c'est une nouvelle frontiere plus a droite
                *pixel_x = *x;
                *pixel_y = *y;
                x_max = *x;
            }
            if (*x == x_max) { //c'est egale a la froitiere la plus a droite deja trouvee
                if (curr_bord == BABORD){ //on remplace que s'il est plus haut
                    if (y_min >= *y) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        y_min = *y;
                    }
                } else { //on remplace que s'il est plus bas s
                    if (y_max <= *y) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        y_max = *y;
                    }
                }
            }
        }
    }
    *new_pixel_x = (*pixel_x+1)%width;
    *new_pixel_y = *pixel_y;
}

void south_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords) {
    int y_max = 0;
    int x_max = 0;
    int x_min = width;

    for (int k = 0; k < count_coords; k++) {
            
        *x = block_coords_x[k];
        *y = block_coords_y[k];

        if (!color_cmp(image2D[*y][*x], image2D[(*y+height+1)%height][*x])) { //le pixel d'en bas n'a pas la meme couleur
            if (*y > y_max) { //c'est une nouvelle frontiere plus en bas
                *pixel_x = *x;
                *pixel_y = *y;
                y_max = *y;
            }
            if (*y == y_max) {
                if (curr_bord == BABORD){ 
                    if (x_max <= *x) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        x_max = *x;
                    }
                } else { 
                    if (x_min >= *x) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        x_min = *x;
                    }
                }
            }
        }
    }
    *new_pixel_x = *pixel_x;
    *new_pixel_y = (*pixel_y+1)%height;
}

void west_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords) {
    int x_min = width;
    int y_max = 0;
    int y_min = height;

    for (int k = 0; k < count_coords; k++) {
            
        *x = block_coords_x[k];
        *y = block_coords_y[k];

        if (!color_cmp(image2D[*y][*x], image2D[*y][(*x+width-1)%width])) { //le pixel de gauche n'a pas la meme color
            if (*x < x_min) { //c'est une nouvelle frontiere plus a gauche
                *pixel_x = *x;
                *pixel_y = *y;
                x_min = *x;
            }
            if (*x == x_min) {
                if (curr_bord == BABORD){ 
                    if (y_max <= *y) { 
                        *pixel_x = *x;
                        *pixel_y = *y;
                        y_max = *y;
                    }
                } else { 
                    if (y_min >= *y) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        y_min = *y;
                    }
                }
            }
        }
    }
    *new_pixel_x = (*pixel_x-1+width)%width;
    *new_pixel_y = *pixel_y;
}

void north_frontier(pixel** image2D, int* pixel_x, int* pixel_y, int* x, int* y, int* new_pixel_x, int* new_pixel_y, int height, int width, enum Bord curr_bord, int* block_coords_x, int* block_coords_y, int count_coords) {
    int y_min = height;
    int x_min = width;
    int x_max = 0;

    for (int k = 0; k < count_coords; k++) {
            
        *x = block_coords_x[k];
        *y = block_coords_y[k];

        if (!color_cmp(image2D[*y][*x], image2D[(*y+height-1)%height][*x])) { 
            if (*y < y_min) { 
                *pixel_x = *x;
                *pixel_y = *y;
                y_min = *y;
            }
            if (*y == y_min) { //pas de else if il faut quand meme l'executer pour actualiser la valeur de xmin au cas ou 
                if (curr_bord == BABORD){ 
                    if (x_min >= *x) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        x_min = *x;
                    }
                } else { 
                    if (x_max <= *x) {
                        *pixel_x = *x;
                        *pixel_y = *y;
                        x_max = *x;
                    }
                }
            }
        }
    }
    *new_pixel_x = *pixel_x;
    *new_pixel_y = (*pixel_y-1+height)%height;
}



void next_coords(pixel** image2D, int* curr_x, int* curr_y, enum Dir* curr_dir, enum Bord* curr_bord, int width, int height, int* attempts, stack* s, int* direction_count, int debug_mode) { 
    //tested is a 2D-array used to store the coordinates of the pixels we already tested in this iteration
    //therefor it must be reset every time next_coords is called
    int** tested = NULL;
    tested = malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        tested[i] = malloc(sizeof(int) * width);
    }

    //block_coords are the coordinates of the pixels belonging to the block that is being tested
    //less coords than height*width (number of pixel of the image) are going to be tested
    //that is why we choose this for the malloc
    int* block_coords_x = malloc(height*width*sizeof(int)); 
    int* block_coords_y = malloc(height*width*sizeof(int));
    int count_coords = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tested[i][j] = 0;
        }
    }

    //exploration fill block_coords_x and block_coords_y (cf block.h)
    exploration(image2D, tested, image2D[*curr_y][*curr_x] , *curr_x, *curr_y, block_coords_x, block_coords_y, &count_coords, width, height);

    //variables used to compute the next coordinates of the cursors
    int pixel_x;
    int pixel_y;
    int x; 
    int y; 
    int new_pixel_x; //next coordinates of the cursor
    int new_pixel_y; //next coordinates of the cursor

    //the right fonction is called depending on the current direction
    if (*curr_dir == EAST) {
        east_frontier(image2D, &pixel_x, &pixel_y, &x, &y, &new_pixel_x, &new_pixel_y, height, width, *curr_bord, block_coords_x, block_coords_y, count_coords);        
    } else if (*curr_dir == SOUTH) {
        south_frontier(image2D, &pixel_x, &pixel_y, &x, &y, &new_pixel_x, &new_pixel_y, height, width, *curr_bord, block_coords_x, block_coords_y, count_coords);
    } else if (*curr_dir == WEST) {
        west_frontier(image2D, &pixel_x, &pixel_y, &x, &y, &new_pixel_x, &new_pixel_y, height, width, *curr_bord, block_coords_x, block_coords_y, count_coords);
    } else if (*curr_dir == NORTH) {
        north_frontier(image2D, &pixel_x, &pixel_y, &x, &y, &new_pixel_x, &new_pixel_y, height, width, *curr_bord, block_coords_x, block_coords_y, count_coords);
    }

    pixel* pix = &(image2D[new_pixel_y][new_pixel_x]); //used to simplify writting

    double luminance = 0.202*(*pix)[0] + 0.707*(*pix)[1] + 0.071*(*pix)[2];

    if (in_coding_colors(*pix)) { //coding color
        *(direction_count) = 0;
        //we must verify if the last pixel was a passing one or a coding one. and *curr_y *curr_x still store the coordinates
        //of the last pixel
        if (in_coding_colors(image2D[*curr_y][*curr_x])) {
            action(s, curr_dir, curr_bord, image2D[*curr_y][*curr_x], image2D[new_pixel_y][new_pixel_x], count_coords, debug_mode, new_pixel_x, new_pixel_y);
        }
        
        //set the coordinates of the new pixel and the number of attempts to 0
        *curr_x = new_pixel_x;
        *curr_y = new_pixel_y;
        *attempts = 0;

    } else if (luminance < 128) {//blocking color
        //we change side and direction alternatively depending on the value of direction_count
        if ((*direction_count)%2 == 0) {
            *curr_bord = (*curr_bord+1)%2; 
        } else {
            *curr_dir = (*curr_dir+1)%4;
        }
        *(direction_count) = (*(direction_count) + 1)%2;

    } else { //passing color

        //we store the first passing coordinates because if we encounter a blocking color
        //we need to come back to those coordinates
        int first_passing_x = new_pixel_x;
        int first_passing_y = new_pixel_y;
        int passing_color = 1;

        //TERMINATION : the cursor will encounter either a passing or a coding color at some point
        //and so passing_color will be equal to 0 and so the while loop will end
        while (passing_color) {
            //the cursors keeps on moving forward until it founds any other thing than a passing color
            if(*curr_dir == EAST) {
                new_pixel_x = (new_pixel_x+1)%width;
                new_pixel_y = new_pixel_y;
            } else if(*curr_dir == SOUTH){
                new_pixel_x = new_pixel_x;
                new_pixel_y = (new_pixel_y+1)%height;
            } else if(*curr_dir == WEST){
                new_pixel_x = (new_pixel_x-1+width)%width;
                new_pixel_y = new_pixel_y;
            } else {
                new_pixel_x = new_pixel_x;
                new_pixel_y = (new_pixel_y-1+height)%height;
            }
            pix = &(image2D[new_pixel_y][new_pixel_x]); //used to simplify writting

            double luminance = 0.202*(*pix)[0] + 0.707*(*pix)[1] + 0.071*(*pix)[2];

            if (in_coding_colors(*pix)) { //coding color
                //we found a coding color so we set the current coordinates to this pixel
                *curr_x = new_pixel_x;
                *curr_y = new_pixel_y;
                *attempts = 0;
                passing_color = 0;
            } else if (luminance < 128) { //blocking color
                //we come back to the first passing
                *curr_x = first_passing_x;
                *curr_y = first_passing_y;
                *attempts = 0;
                passing_color = 0;
            } 
        }
    }

    //FREE
    for (int i = 0; i < height; i++) {
        free(tested[i]);
    }
    free(tested);
    free(block_coords_x);
    free(block_coords_y);
}

