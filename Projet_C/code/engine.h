#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include "list_opacity.h"
#include "matrix.h"

typedef struct Point{
    int x;  //Abscisse
    int y;  //Ordonnée
} Point;

typedef struct Node_point{
    Point v;                    //Valeur du maillon
    struct Node_point *next;    //Suite de la liste chainée
}*List_point;

typedef struct engine{
    int x;                   //Abscisse du pixel courant
    int y;                   //Ordonée du pixel courant
    int xm;                  //Abscisse du pixel marqué
    int ym;                  //Ordonée du pixel marqué
    int cap;                 //Direction du curseur : 0=Nord; 1=Est; 2=Sud; 3=Ouest (raisonnement modulo 4)
    List bucket_color;       //Sceau de couleurs   
    List_op bucket_opacity;  //Sceau d'opacité
    stack layers;            //Pile de calques
} engine;

/*
@requires: nothing
@assigns: e (e.c)
@ensures: change le cap de e (rotation dans le sens horaire)
*/
void turn_right(engine* e);

/*
@requires: nothing
@assigns: e (e.c)
@ensures: change le cap de e (rotation dans le sens anti-horaire)
*/
void turn_left(engine* e);

/*
@requires: nothing
@assigns: e (e.xm et e.ym)
@ensures: modifie la position marquée par la position actuelle
*/
void position_marked(engine* e);

/*
@requires: nothing
@assigns: e (e.x et e.y)
@ensures: avance d'une cellule de la matrice dans la direction du cap;
*/
void go_forward(engine * e);

/*
@requires: nothing
@assigns: nothing
@ensures: retourne le pixel courant calculé à partir des sceaux de couleur et d'opacité
*/
pixel current_pixel(List_op o,List c);

/*
@requires: size > 0
@assigns: nothing
@ensures: renvoie un type "engine" initialisé selon le sujet
*/
engine initialize_engine(int size);

/*
@requires: nothing
@assigns: e (e.stack)
@ensures: modifie la pile de calques en fusionnant comme expliqué dans le sujet les deux calques les plus hauts de la pile
*/
void fusion_layer_final(engine *e);

/*
@requires: nothing
@assigns: e (e.stack)
@ensures: Découpe le calque situé juste en dessous du sommet de la pile en utilisant comme masque les opacités de celui au sommet, si la pile ne contient qu'un seul calque, ne fait rien
*/
void cut_layer_final(engine *e);

/*
@requires: nothing
@assigns: nothing
@ensures: retourne l'entier le plus grand entre x et y
*/
int max(int x, int y);

/*
@requires: nothing
@assigns: e (e.stack)
@ensures: modifie le claque le plus haut de la pile en traçant une ligne entre le pixel marqué et actuelle avec la couleur et opacité du pixel courant
*/
void line_trace(engine* e);

/*
@requires: size > 0
@assigns: nothing
@ensures: vérifie que les coordonnées (x,y) existent bien dans la matrice carré de taille size 
*/
int is_valid(int x, int y,int size);

/*
@requires: nothing
@assigns: nothing
@ensures: retourne une List_point vide
*/
List_point create_empty_point();
/*
@requires: nothing
@assigns: nothing
@ensures: retourne un bouléen (donc en C 0 ou 1) en fonction de si la List_point l est vide ou non
*/
int is_empty_point(List_point l);

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie une List_point ayant ayant pour première valeur e et ayant l comme la liste suivante (Ajoute e à la List_point)
*/
List_point make_point(Point e, List_point l);

/*
@requires: nothing
@assigns: l
@ensures: ajoute e à la liste l
*/
void add_point(Point e, List_point *l);

/*
@requires: l non vide
@assigns: *l
@ensures: renvoie tout en supprimant de la liste l la première valeur de l (et libère la mémoire allouée)
*/
Point pop_point(List_point *l);

/*
@requires: nothing
@assigns: m
@ensures: change toutes les pixels de m qui sont comme old par des pixels comme new par une diffusion classique (se propage de proche en proche)
*/
void flood_fill(int x, int y, pixel old, pixel new,matrix *m);
#endif