#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "extract.h"
#include "block.h"


int main(int argc, char* argv[]) {

    //show an error and exit if the program is not launched with one argument
    int debug_mode;
    if (argc == 3) { //if debug mode activ

        if (!(strcmp(argv[2], "-debug"))) {
            printf("DEBUG MODE\n");
            debug_mode = 1;
        }
        else {
            perror("ERROR : usage ./prog name_of_file.ppm"); // there is 2 argument but the second one is unkown
            exit(1);
        }

    } else if (argc != 2) { //there is not 1 argument
        perror("ERROR : usage ./prog name_of_file.ppm");
        exit(1);

    } else {
        debug_mode = 0; //there is one argument but the mode is not debug
    }

    FILE *f = fopen(argv[1], "r");
    
    //construction image2D
    int width, height;
    pixel** image2D = image_extract(f, &width, &height);
    
    //cursors inital coordinates 
    int curr_x = 0;
    int curr_y = 0; 

    //cursors inital side and direction 
    enum Bord curr_bord = BABORD;
    enum Dir curr_dir = EAST;

    //initialisation of the int stack
    stack int_stack;
    stack* pint_stack = &int_stack;
    stack_init(pint_stack);

    int attempts = 0; // if this variable exceeds 8, then the program end
    int direction_count = 0; //direction_count is used as a counter to know if we must change direction or side

    //TERMINATION : it depends on the ppm that is used as an input because attempts can be set to 0 in next_coords
    //if the cursor is confronted to 8 blocking pixels in a row the program stops
    //because attempts is only being removed when a coding or passing pixel is found (see next_coords)
    while (attempts < 8) {
        next_coords(image2D, &curr_x, &curr_y, &curr_dir, &curr_bord, width, height, &attempts, pint_stack, &direction_count, debug_mode);
        attempts++;
    }


    //FREE
    for(int i = 0; i<height; i++) { 
        free(image2D[i]);
    }
    free(image2D); 
    free(pint_stack->tab);

    return 0;
}