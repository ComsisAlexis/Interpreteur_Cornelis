#include "color.h"


int color_cmp(pixel pixel1, pixel pixel2) {
    for (int k = 0; k<3; k++) {
        if (pixel1[k] != pixel2[k]) { //if at least on of the 3 values is not equal
            return 0;   //then the pixels are not of the same color
        }
    }
    return 1;
}

void pixel_fill(pixel p, unsigned char r, unsigned char g, unsigned char b) {
    p[0] = r; 
    p[1] = g;
    p[2] = b;
}

enum Brightness pixel_brightness(pixel p) { 
    int count_bright = 0;
    int count_dark = 0;

    //we notice that the bright colors and the bright colors only have no value equals to 0
    //we notice that the dark colors and the dark colors only have no value equals to 255

    for (int k = 0; k < 3; k++) {
        if (p[k] > 0) {
            count_bright++;
        }
        if (p[k] != 255) {
            count_dark++;
        }
    }
    if (count_bright == 3) {
        return BRIGHT; //returns BRIGHT if there are 3 values > 0
    }else if (count_dark == 3) {
        return DARK; //DARK if there are no value = 255
    }
    return MEDIUM; //MEDIUM otherwise
}

enum Color pixel_color(pixel p) {
    if(p[0] > p[1]) { //RED and MAGENTA are the only one verifying this property
        if (p[1] == p[2]) { //RED is the only on verifying this
            return RED;
        } 
        return MAGENTA;  
    } else if (p[1] > p[2]) { //YELLOW AND GREEN
        if (p[0] == p[1]) { //YELLOW
            return YELLOW;
        }
        return GREEN;
    } else if (p[1] == p[2]) { //CYAN
        return CYAN;
    }
    return BLUE; //BLUE
}

int in_coding_colors(pixel p) {
    pixel coding_colors[18];
    pixel_fill(coding_colors[0], 255, 128, 128);
    pixel_fill(coding_colors[1], 255, 255, 128);
    pixel_fill(coding_colors[2], 128, 255, 128);
    pixel_fill(coding_colors[3], 128, 255, 255);
    pixel_fill(coding_colors[4], 128, 128, 255);
    pixel_fill(coding_colors[5], 255, 128, 255);
    pixel_fill(coding_colors[6], 255, 0, 0);
    pixel_fill(coding_colors[7], 255, 255, 0);
    pixel_fill(coding_colors[8], 0, 255, 0);
    pixel_fill(coding_colors[9], 0, 255, 255);
    pixel_fill(coding_colors[10], 0, 0, 255);
    pixel_fill(coding_colors[11], 255, 0, 255);
    pixel_fill(coding_colors[12], 128, 0, 0);
    pixel_fill(coding_colors[13], 128, 128, 0);
    pixel_fill(coding_colors[14], 0, 128, 0);
    pixel_fill(coding_colors[15], 0, 128, 128);
    pixel_fill(coding_colors[16], 0, 0, 128);
    pixel_fill(coding_colors[17], 128, 0, 128);

    
    for (int k = 0; k < 18; k++) {
        //test if the color we are testing is equal to any of the coding colors
        if (color_cmp(p, coding_colors[k])) {
            return 1;
        }
    }
    return 0;
}

int max(int e1, int e2) {
    if (e1>e2) {
        return e1;
    }
    return e2;
}

//We must give the differences according to the cycles given in the subject
//that is why we must add by 3 and then take the remainder out of 3 (because it is a cycle)
int pixel_diff_brightness(pixel last_p, pixel current_p) {
    int diff = pixel_brightness(current_p) - pixel_brightness(last_p);
    return((diff+3)%3);
    
}
//and that is why we must add by 6 and then take the remainder out of 6 (because it is a cycle)
int pixel_diff_color(pixel last_p, pixel current_p) {
    int diff = pixel_color(current_p) - pixel_color(last_p);
    return((diff+6)%6);
}