#ifndef __EXTRACT_H
#define __EXTRACT_H

#include "color.h"

/*  @requires *f an valid opened ppm file;
    @assigns **image2D, btm, *img_width, *img_height;
    @ensures return a two-dimensional array containing the pixel of the image in the file storing in *img_width and *img_height
    its width and its height;*/
pixel** image_extract(FILE *f, int *img_width, int *img_height);

#endif