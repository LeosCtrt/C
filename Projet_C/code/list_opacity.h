#ifndef LIST_OPACITY_H
#define LIST_OPACITY_H

#include <stdlib.h>
#include <stdio.h>
typedef unsigned char value_op; //On définit valeur

typedef struct Node_op {
    value_op v;             //Valeur du maillon
    struct Node_op *next;   //Suite de la liste chaînée
}*List_op;

/*
@requires: nothing
@assigns: nothing
@ensures: retourne une List_op vide
*/
List_op create_empty_op();

/*
@requires: nothing
@assigns: nothing
@ensures: retourne un "bouléen" (donc en C 0 ou 1) en fonction de si la List_op l est vide ou non
*/
int is_empty_op(List_op l);

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie une List_op ayant ayant pour première valeur e et ayant l comme reste de la List_op (qui a ajoutée e à la List_op)
*/

List_op make_op(value_op e, List_op l);

/*
@requires: nothing
@assigns: l
@ensures: Ajoute e à l
*/
void add_op(value_op e, List_op *l);

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne la taille de l
*/
int len_list_op(List_op l);

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne la moyenne des éléments de l
*/
int avg_sum_list_op(List_op l);

/*
@requires: nothing
@assigns: o
@ensures: Ajoute la transparence totale (0) à l
*/
void add_opacity_min(List_op *o);

/*
@requires: nothing
@assigns: o
@ensures: Ajoute l'opacité totale (255) à l
*/
void add_opacity_max(List_op *o);

/*
@requires: nothing
@assigns: o
@ensures: Vide la List_op (tout en libérant l'espace alloué aux valeurs au fur et à mesure)
*/
void empty_bucket_op(List_op *o);

#endif