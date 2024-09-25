#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct pixel{    //Définition d'un pixel (une couleur + une opacité)
    color c;
    unsigned char op;
}pixel;

typedef struct matrix{
    int size; 
    pixel** cells;} matrix;   //Structure d'une matrice de pixels carré de taille size

typedef struct stack {
    matrix stack[10];
    int top;
}stack;

/*
@requires : size >= 0
@assigns : nothing
@ensures : créé une matrice de pixels de taille size ayant chaque cellules initialisées à (0,0,0) 0
*/
matrix matrix_create(int size); 

/*
@requires : nothing
@assigns : nothing
@ensures : libère l'espace alloué à la matrice
*/
void matrix_free(matrix *m);

/*
@requires: nothing
@assigns: c0, c1
@ensures: renvoie une matrice résultat qui est la fusion des deux calques c0 et c1 comme demandé dans l'énoncé, libère l'espace alloué à c0 et c1
*/
matrix layer_fusion(matrix* c0, matrix* c1);

/*
@requires: nothing
@assigns: c0, c1
@ensures: renvoie une matrice résultat qui est le découpage du calque c0 en utilisant comme masque les opacités de c1 comme demandé dans l'énoncé, libère l'espace alloué à c0 et c1
*/
matrix cut_layers(matrix *c0,matrix *c1);

/*
requires: nothing
assigns: nothing
ensures: retourne une pile vide
*/
stack stack_new();
/*
requires: nothing
assigns: nothing
ensures: retourne un "bouléen" (donc en C 0 ou 1) en fonction de si la pile s est vide ou non
*/
int stack_isEmpty(stack s);

/*
requires: nothing
assigns: s (s.stack, s.top)
ensures: Ajoute m en haut de la pile s
*/
void stack_push(stack *s, matrix m);

/*
requires: nothing
assigns: s (s.stack, s.top)
ensures: renvoie la matrice en haut de la pile s et la supprime de la pile
*/
matrix pop(stack *s);

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie la taille de la pile
*/
int stack_length(stack*s);

/*
@requires: nothing
@assigns: nothing
@ensures: libère ll'espace alloué aux éléments de la pile (ici aux matrices dans la pile)
*/
void free_layers(stack* s);

/*
@requires: nothing
@assigns: nothing
@ensures: Ajoute un nouveau calque à la pile, si il y a déjà 10 calques, ne fait rien
*/
void stack_add_new_layer(matrix m,stack *s);

#endif