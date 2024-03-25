#include <stdlib.h>
#include "stack.h"


void stack_init(stack *s) {
    s->tab = NULL;
    s->current_size = 0;
}


int stack_is_empty(stack s) {
    return(s.current_size == 0);
}

void stack_add(stack *s, int val) {
    s->current_size++;
    s->tab = realloc(s->tab, s->current_size * sizeof(int));    
    s->tab[s->current_size-1] = val;
}


void stack_show(stack *s) {
    int cst_size = s->current_size;
    int element;
    printf("Stack : ");
    stack tmp_stack;
    stack_init(&tmp_stack);
    for (int k = 0; k<cst_size; k++) {
        element = stack_pop(s);
        printf("%d ", element);
        stack_add(&tmp_stack, element);
    }
    for (int k = 0; k<cst_size; k++) {
        element = stack_pop(&tmp_stack);
        printf("%d ", element);
        stack_add(s, element);
    }
    free((&tmp_stack)->tab);
    printf("\n");
}

//empile
void stack_size_add(stack *s, int size_last_block) {
    stack_add(s, size_last_block);
}

//depile
int stack_pop(stack *s) {
    s->current_size--;
    int tmp_res = s->tab[s->current_size];
    s->tab = realloc(s->tab, s->current_size * sizeof(int));
    
    return(tmp_res);
}

//plus
void stack_plus(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        stack_add(s, element1 + element2);
    }
}

//moins
void stack_minus(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        stack_add(s, element2 - element1);
    }
}

//fois
void stack_prod(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        stack_add(s, element1 * element2);
    }
}

//divise
void stack_divide(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        stack_add(s, element2 / element1);
    }
}

//reste
void stack_remainder(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        stack_add(s, element2 % element1);
    }
}

//non
void stack_not(stack *s) {
    if (s->current_size > 0) {
        int element = stack_pop(s);
        if (element == 0) {
            stack_add(s, 1);
        } else {
            stack_add(s, 0);
        }
    }
}

//plus grand
void stack_greater(stack *s) {
    if (s->current_size > 1) {
        int element1 = stack_pop(s);
        int element2 = stack_pop(s); 
        if (element2 > element1) { //we can replace it by >= sometimes. cf the third paragraph of the report
            stack_add(s, 1);       
        } else {
            stack_add(s, 0);
        }
    }
}

//direction
void stack_turn(stack *s, enum Dir* dir) { 
    if (s->current_size > 0) {
        int nb_turn = stack_pop(s);
        for (int k = 0; k < nb_turn; k++) {
            *dir = (*dir+1)%4;
        }
    }
}

//bord
void stack_side(stack*s, enum Bord* bord) {
    if (s->current_size > 0) {
        int nb_change = stack_pop(s);
        if (nb_change%2==1) {
            *bord = (*bord+1)%2;
        }
    }
}

//duplique
void stack_duplicate(stack *s) {
    if (s->current_size > 0) {
        int element = stack_pop(s);
        stack_add(s, element);
        stack_add(s, element);
    }
}

//tourne
void turn(stack *s) {
    int occurence;
    int depth;
    if (s->current_size > 2) { 
        occurence = stack_pop(s);
        depth = stack_pop(s);
    
        if (s->current_size >= depth) {
            stack tmp1;
            stack tmp2;
            stack_init(&tmp1);
            stack_init(&tmp2);
    
            for (int k = 0; k < occurence; k++) { //we are turning "occurence" time
                stack_add(&tmp1, stack_pop(s));
                for (int i = 0; i < depth-1; i++) { //and we go the depth "depth"
                    stack_add(&tmp2, stack_pop(s));
                }
                stack_add(s, stack_pop(&tmp1));
                for (int i = 0; i < depth-1; i++) {
                    stack_add(s, stack_pop(&tmp2));
                }
            }
            free(tmp1.tab);
            free(tmp2.tab);
        } else {
            stack_add(s, depth);
            stack_add(s, occurence);
        }
    }
}

//in(nombre)
void in_number(stack *s) {
    int element;
    scanf("%d", &element);
    stack_add(s, element);
}

//in(char)
void in_char(stack *s) {
    char element;
    element = getc(stdin);
    stack_add(s, (int)element); //we need to cast it as an integer
    
}

//out(nombre)
void out_number(stack *s) {
    if (s->current_size > 0) {
        int element = stack_pop(s);
        printf("%d\n", element);
    }
}

//out(char)
void out_char(stack *s) {
    if (s->current_size > 0) {
        int element = stack_pop(s);
        printf("%c", element);
    }
}

