#include <stdlib.h>
#include <stdio.h>
#include "list_opacity.h"

List_op create_empty_op() {
    return NULL;
}

int is_empty_op(List_op l) {
    return l == NULL;
}

List_op make_op(value_op e, List_op l) {
    List_op res = malloc(sizeof(struct Node_op));
    res->v = e;
    res->next = l;
    return res;
}

void add_op(value_op e, List_op *l) {
    *l= make_op(e, *l);
}

int len_list_op(List_op l) {
    int len = 0;

    while (NULL != l) {  //Fin quand l est vide (l==NULL)
        len += 1;
        l = l->next;
    }
    return len;
}

int avg_sum_list_op(List_op l) {
    int sum=0;
    int a =len_list_op(l);
    while (NULL != l) { //Fin quand l est vide (l==NULL)
        sum = sum + (int)l->v;
        l = l->next;
    }
    sum=sum/a;
    return sum;
}

void add_opacity_min(List_op *o){
    add_op(0,o);
}

void add_opacity_max(List_op *o){
    add_op(255,o);
}

void empty_bucket_op(List_op *o){
    while(!is_empty_op(*o)){ //Fin quand l est vide (l==NULL)
        List_op nextnode = (*o)->next;
        free(*o);
        (*o)=nextnode;}
}