#ifndef __COLOR_H
#define __COLOR_H

#include <stdio.h>

enum Brightness { //BRIGHT(0) -> MEDIUM(1) -> DARK(2) -> BRIGHT(0)
    BRIGHT,
    MEDIUM,
    DARK
};

enum Color { //RED(0) -> YELLOW(1) -> GREEN(2) -> CYAN(3) -> BLUE(4) -> MAGENTA(5) -> RED(0)
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA
};

typedef unsigned char pixel[3];  //RED(0) GREEN(1) BLUE(2)

/*  @requires pixel1 and pixel2 initialised;
    @assigns nothing;
    @ensures return 1 if the pixels are of the same color and 0 otherwise;*/
int color_cmp(pixel pixel1, pixel pixel2);

/*  @requires nothing;
    @assigns p;
    @ensures fill the pixel p with the color (r, g, b);*/
void pixel_fill(pixel p, unsigned char r, unsigned char g, unsigned char b);

/*  @requires p an initialised pixel;
    @assigns nothing;
    @ensures return the brightness (enum Brightness) of the pixel p;*/
enum Brightness pixel_brightness(pixel p);

/*  @requires p an initialised pixel;
    @assigns nothing;
    @ensures return the color (enum Color) of the pixel p;*/
enum Color pixel_color(pixel p);

/*  @requires p an initialised pixel;
    @assigns nothing;
    @ensures return 1 if p is a coding color and 0 otherwise;*/
int in_coding_colors(pixel p);

/*  @requires nothing;
    @assigns nothing;
    @ensures return the max between e1 and e2;*/
int max(int e1, int e2);

/*  @requires last_p and current_p initialised pixels;
    @assigns nothing;
    @ensures return the difference of brightness (according to the cycle) between the pixel;*/
int pixel_diff_brightness(pixel last_p, pixel current_p);

/*  @requires last_p and current_p initialised pixels;
    @assigns nothing;
    @ensures return the difference of color (according to the cycle) between the pixel;*/
int pixel_diff_color(pixel last_p, pixel current_p);

#endif