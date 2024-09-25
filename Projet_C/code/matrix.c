#include "matrix.h"

matrix matrix_create(int size) {
    matrix m;
    m.size = size;
    m.cells = malloc(size * sizeof(pixel*));
    for (int i = 0; i < size; i++) {m.cells[i] = malloc(size * sizeof(pixel));}
    for (int i = 0; i < size; i++) {
        for(int j = 0; j<size; j++){
            m.cells[i][j].op  = 0;
            m.cells[i][j].c.r = 0;
            m.cells[i][j].c.g = 0;
            m.cells[i][j].c.b = 0;
            }
        }

    return m;
}

void matrix_free(matrix *m){
    for(int i = 0; i < m->size; i++){free(m->cells[i]);}
    free(m->cells);
}

matrix layer_fusion(matrix* c0, matrix* c1){
    matrix resultat = matrix_create(c0->size);
    for(int i = 0; i<c0->size; i++){
        for(int j = 0; j<c0->size; j++){
            unsigned char opacity_current = c0->cells[i][j].op;
            resultat.cells[i][j].c.r = c0->cells[i][j].c.r + (c1->cells[i][j].c.r * (255-opacity_current)/255);
            resultat.cells[i][j].c.g = c0->cells[i][j].c.g + (c1->cells[i][j].c.g * (255-opacity_current)/255);
            resultat.cells[i][j].c.b = c0->cells[i][j].c.b + (c1->cells[i][j].c.b * (255-opacity_current)/255);
            resultat.cells[i][j].op  = c0->cells[i][j].op  + (c1->cells[i][j].op  * (255-opacity_current)/255);
        }
    }
    matrix_free(c0);
    matrix_free(c1);
    return resultat;
}

matrix cut_layers(matrix *c0,matrix *c1){
    matrix resultat = matrix_create(c0->size);
    for(int i = 0; i<c0->size; i++){
        for(int j = 0; j<c0->size; j++){
            unsigned char opacity_current = c0->cells[i][j].op;
            resultat.cells[i][j].c.r = c1->cells[i][j].c.r * opacity_current /255;
            resultat.cells[i][j].c.g = c1->cells[i][j].c.g * opacity_current /255;
            resultat.cells[i][j].c.b = c1->cells[i][j].c.b * opacity_current /255;
            resultat.cells[i][j].op  = c1->cells[i][j].op  * opacity_current /255;
        }
    }
    matrix_free(c0);
    matrix_free(c1);
    return resultat;

}

stack stack_new() {
    stack s;
    s.top = -1;
    return s;
}

int stack_isEmpty(stack s) {
    return (s.top < 0);
}

void stack_push(stack *s, matrix m) {
    if (s->top == 10) {
        return;
    }
    s->top += 1;
    s->stack[s->top] = m;
}

matrix pop(stack *s) {
    matrix e = s->stack[s->top];
    s->top -= 1;
    return e;
}

int stack_length(stack*s){
    stack copy=*s;
    int len=0;
    while(!stack_isEmpty(copy)){ //Fin quand copy est vide
        len+=1;
        pop(&copy);
    }
    return len;
}

void free_layers(stack* s){
    while(!stack_isEmpty(*s)){  //Fin quand s est vide
        matrix_free(&s->stack[s->top]);
        pop(s);
    }
}

void stack_add_new_layer(matrix m,stack *s){
    if(stack_length(s)<10){ stack_push(s,m);}
}