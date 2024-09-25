#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color;

typedef color value;   

typedef struct Node {
    value v;
    struct Node *next;
}*List;

/*
@requires: nothing
@assigns: nothing
@ensures: retourne une liste vide
*/
List create_empty();

/*
@requires: nothing
@assigns: nothing
@ensures: retourne un "bouléen" (donc en C 0 ou 1) en fonction de si la List l est vide ou non
*/
int is_empty(List l);

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie une List_op ayant ayant pour première valeur e et ayant l comme reste de la List_op (qui a ajoutée e à la List_op)
*/

List make(value e, List l);

/*
@requires: nothing
@assigns: l
@ensures: Ajoute e à l
*/

void add(value e, List *l);

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne la taille de l
*/
int len_list(List l);


/*
@requires: nothing
@assigns: nothing
@ensures: Retourne la moyenne des éléments de l
*/
color avg_sum_list(List l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur noir à l
*/
void add_color_black_in_the_bucket(List *l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur rouge à l
*/

void add_color_red_in_the_bucket(List *l);

/*
@requires: nothing
@assigns: l
@ensures: Ajoute la couleur verte à l
*/

void add_color_green_in_the_bucket(List *l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur bleu à l
*/
void add_color_blue_in_the_bucket(List *l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur jaune à l
*/
void add_color_yellow_in_the_bucket(List *l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur magenta à l
*/
void add_color_magenta_in_the_bucket(List *l);

/*
@requires:nothing
@assigns: l
@ensures: Ajoute la couleur cyan à l
*/
void add_color_cyan_in_the_bucket(List *l);

/*
@requires:nothing
@assigns:nothing
@ensures: Ajoute la couleur blanc à l
*/
void add_color_white_in_the_bucket(List *l);

/*
@requires: nothing
@assigns: c
@ensures: Vide la List (tout en libérant l'espace alloué aux valeurs au fur et à mesure)
*/
void empty_bucket(List *c);

#endif