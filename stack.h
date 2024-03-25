#ifndef __STACK_H
#define __STACK_H

#include <stdio.h>

struct stack {
    int* tab;
    int current_size;
};

//0 for babord 1 for tribord
enum Bord {
    BABORD,
    TRIBORD
};
//O east 1 south 2 west 3 north
enum Dir {
    EAST,
    SOUTH,
    WEST,
    NORTH
};


typedef struct stack stack;

/*  @requires s a stack that has just been created;
    @assigns *s;
    @ensures s is initialised with no element and a size of 0;*/
void stack_init(stack *s);

/*  @requires s an initialised stack;
    @assigns nothing;
    @ensures returns 1 if the stack is empty and 0 otherwise;*/
int stack_is_empty(stack s);

/*  @requires s an intialised stack;
    @assigns *s;
    @ensures add val at the top of the stack;*/
void stack_add(stack *s, int val);

/*  @requires s an initialised stack;
    @assigns *s;
    @ensures print the stack from the bottom to the top;*/
void stack_show(stack *s);

//empile
/*  @requires s and initialised stack size_last_block the size of the last block;
    @assigns *s;
    @ensures add size_last_block at the top of the stack;*/
void stack_size_add(stack *s, int size_last_block);

//depile
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures delete the element at the top of the stack and return it;*/
int stack_pop(stack *s);

//plus
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push the sum of those two elements;*/
void stack_plus(stack *s);

//moins
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push the difference between the second and the first at the top of the stack;*/
void stack_minus(stack *s);

//fois
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push the product of those two at the top of the stack;*/
void stack_prod(stack *s);

//divise
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push the quotient of the second divided by the first;*/
void stack_divide(stack *s);

//reste
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push the remainder of the second divided by the first;*/
void stack_remainder(stack *s);

//non
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop the top then push 1 if the value poped is equal to 0 and push 0 otherwise (logical NOT);*/
void stack_not(stack *s);

//plus grand
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then push 1 if the second is greater than the first and 0 otherwise;*/
void stack_greater(stack *s);


//direction
/*  @requires s an initialised stack dir the current direction;
    @assigns *s enum Dir*;
    @ensures pop the top of the stack (as nb_turn) then turn the direction enum Dir clockwise nb_turn times;*/
void stack_turn(stack *s, enum Dir* dir);

//bord
/*  @requires s an initialised stack bord the current side;
    @assigns *s enum Bord*;
    @ensures pop the top of the stack (as nb_change) then change the side nb_change times;*/
void stack_side(stack*s, enum Bord* bord);

//duplique
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop the top of the stack then push it twice;*/
void stack_duplicate(stack *s);

//tourne
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop two elements then make the stack "turn" until depth given by second popped element. Do this 
    the number of time given by the first popped element;*/
void turn(stack *s);

//in(nombre)
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures the user enters a number which is pushed on the stack;*/
void in_number(stack *s);

//in(char)
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures the enters a char which is pushed on the stack;*/
void in_char(stack *s);

//out(nombre)
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop the top then print it in stdout */
void out_number(stack *s);

//out(char)
/*  @requires s an initialised stack;
    @assigns *s;
    @ensures pop the top then print the character corresponding to this ASCII code in stdout*/
void out_char(stack *s);


#endif