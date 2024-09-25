#include "list.h"

List create_empty() {
    return NULL;
}

int is_empty(List l) {
    return l == NULL;
}

List make(value e, List l) {
    List res = malloc(sizeof(struct Node));

    res->v = e;
    res->next = l;
    return res;
}

void add(value e, List *l) {
    *l= make(e, *l);
}

int len_list(List l) {
    int len = 0;

    while (NULL != l) { //Fin quand l est vide (l==NULL)
        len += 1;
        l = l->next;
    }
    return len;
}

color avg_sum_list(List l) {
    int ra=0;
    int ba=0;
    int ga=0;
    int a =len_list(l);
    while (NULL != l) { //Fin quand l est vide (l==NULL)
        ra = ra + (int)l->v.r;
        ga = ga + (int)l->v.g;
        ba = ba + (int)l->v.b;
        l = l->next;
    }
    ra=ra/a;
    ga=ga/a;
    ba=ba/a;
    color sum;
    sum.r=ra;
    sum.g=ga;
    sum.b=ba;
    return sum;
}


void add_color_black_in_the_bucket(List *l){
    color c;
    c.r=0;
    c.g=0;
    c.b=0;
    add(c,l);
}


void add_color_red_in_the_bucket(List *l){
    color c;
    c.r=255;
    c.g=0;
    c.b=0;
    add(c,l);
}


void add_color_green_in_the_bucket(List *l){
    color c;
    c.r=0;
    c.g=255;
    c.b=0;
    add(c,l);
}


void add_color_blue_in_the_bucket(List *l){
    color c;
    c.r=0;
    c.g=0;
    c.b=255;
    add(c,l);
}


void add_color_yellow_in_the_bucket(List *l){
    color c;
    c.r=255;
    c.g=255;
    c.b=0;
    add(c,l);
}


void add_color_magenta_in_the_bucket(List *l){
    color c;
    c.r=255;
    c.g=0;
    c.b=255;
    add(c,l);
}

void add_color_cyan_in_the_bucket(List *l){
    color c;
    c.r=0;
    c.g=255;
    c.b=255;
    add(c,l);
}


void add_color_white_in_the_bucket(List *l){
    color c;
    c.r=255;
    c.g=255;
    c.b=255;
    add(c,l);
}

void empty_bucket(List *o){
    while(!is_empty(*o)){ //Fin quand o est vide
        List nextnode = (*o)->next;
        free(*o);
        (*o)=nextnode;}
}