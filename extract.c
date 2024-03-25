#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "extract.h"

pixel** image_extract(FILE *f, int *img_width, int *img_height) {

    char buffer[256]; //buffer to read the ppm file

    int width, height;
    pixel *btm=NULL;

    fgets(buffer, 256, f); //reading the first line
    if (strcmp(buffer, "P6\n")) //returning an error if the type of ppm is not the right one (P6)
        perror("not binary ppm file\n");

    //we ignore all the comments : (lines beginning with a #)
    //TERMINATION : there is not an infinite amount of comments
    //so the while loop ends
    fgets(buffer, 256,f);
    while (buffer[0] == '#') {
        fgets(buffer, 256,f); //the last line that is read here does not verify buffer[0] == "#" 
    }                         //thats why it is the line of width and height
    

    sscanf(buffer, " %d %d " , &width , &height );
    fgets(buffer, 256,f);

    //read the pixels of the file and store them in a 1D-array
    btm = malloc(width * height * sizeof(pixel));
    fread(btm, sizeof(pixel), width*height, f);


    //the 1D-array is turned into a 2D-array in order to simplify manipulations
    pixel **image2D = NULL;
    image2D = malloc(sizeof(pixel*) * height);
    for (int i = 0; i < height; i++) {
        image2D[i] = malloc(sizeof(pixel) * width);
    }

    //the 2D-array is then filled with the values
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            for (int k = 0; k < 3; k++) {
                image2D[h][w][k] = btm[h*width + w][k]; //we copy each value (R, G, B) from each pixel 
            }
        }
    }

    //we use those pointers to use height and width in the main function
    *img_height = height;
    *img_width = width;

    free(btm);

    return image2D;
}