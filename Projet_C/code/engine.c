#include "engine.h"

void turn_right(engine* e){
    e->cap=(e->cap+1)%4;
}

void turn_left(engine* e){
    e->cap=(e->cap-1)%4;
    while(e->cap<0){e->cap = e->cap + 4;} //Fin quand e->cap >= 0 
}

void position_marked(engine* e){
    e->xm=e->x;
    e->ym=e->y;
}

void go_forward(engine * e){
    int size=e->layers.stack[e->layers.top].size;
    if(e->cap==0){e->x-=1;if(e->x<0){e->x=e->x+size;}}
    if(e->cap==1){e->y+=1;if(e->y>size-1){e->y=e->y-size;}}
    if(e->cap==2){e->x+=1;if(e->x>size-1){e->x=e->x-size;}}
    if(e->cap==3){e->y-=1;if(e->y<0){e->y=e->y+size;}}
}

pixel current_pixel(List_op o,List c){
    pixel p;
    if(is_empty_op(o)){p.op=255;}
    else {p.op=avg_sum_list_op(o);}
    if(is_empty(c)){
        p.c.r = 0;
        p.c.g = 0;
        p.c.b = 0;
    }
    else{p.c=avg_sum_list(c);
    p.c.r=(p.c.r*p.op)/255;
    p.c.g=(p.c.g*p.op)/255;
    p.c.b=(p.c.b*p.op)/255;}
    return p;
}

engine initialize_engine(int size){
    engine e;
    e.cap = 1; //Définition du cap de base
    e.x = 0; e.y = 0; //On initialise la position à (0,0)
    e.xm = 0; e.ym = 0; //On initialise le pixel marqué à (0,0)
    e.layers = stack_new(); //On crée la pile de calques
    stack_add_new_layer(matrix_create(size),&e.layers); //On ajoute le premier calque à la pile
    e.bucket_color = create_empty(); //On crée le sceau de couleur
    e.bucket_opacity = create_empty_op(); //On crée le sceau d'opacité
    return e;
}

void fusion_layer_final(engine *e){
    if(stack_length(&e->layers)==1){}
    else {
        matrix top,under_top;
        top=pop(&e->layers);
        under_top=pop(&e->layers);
        stack_add_new_layer(layer_fusion(&top,&under_top),&e->layers);}
}

void cut_layer_final(engine *e){
    if(stack_length(&e->layers)<=1){}
    else {
        matrix top,under_top;
        top=pop(&e->layers);
        under_top=pop(&e->layers);
        stack_add_new_layer(cut_layers(&top,&under_top),&e->layers);}
}
int max(int x, int y){
    if(x>y){return x;}
    else {return y;}
}
void line_trace(engine* e){
    int dx,dy,d,s,x,y,i;
    dx = e->xm - e->x;
    dy = e->ym - e->y;
    d = max(abs(dx),abs(dy));
    s = 1;
    if ((dx!=0) && (dy!=0) && ( ((dx<0) && (dy<0)) || ((dx>0) && (dy>0)))){ s=0;}
    pixel p = current_pixel(e->bucket_opacity,e->bucket_color);
    x = e->x * d + (d-s)/2;
    y = e->y * d + (d-s)/2;
    for(i = 0; i<d; i++){
        e->layers.stack[e->layers.top].cells[x/d][y/d] = p;
        x = x + dx;
        y = y + dy;
    }
    e->layers.stack[e->layers.top].cells[e->xm][e->ym] = p;
}
/*
void fill(int x, int y, pixel old, pixel new, matrix *m){
    if((old.c.r==new.c.r) && (old.c.g==new.c.g) && (old.c.b==new.c.b) && (old.op==new.op)){}
    else{
        if((m->cells[x][y].c.r==old.c.r) && (m->cells[x][y].c.g==old.c.g) && (m->cells[x][y].c.b==old.c.b) && (m->cells[x][y].op==old.op)){
            m->cells[x][y]=new;
            if(x > 0 && m->cells[x - 1][y] == old){x-=1; add(); x+=1}
            if(y > 0){fill(x, y-1, old, new, m);}
            if(x < m->size-1){fill(x+1, y, old, new, m);}
            if(y < m->size-1){fill(x, y+1, old, new, m);}
        }
    }

}
*/

int is_valid(int x, int y,int size) {
    return (x >= 0 && x < size && y >= 0 && y < size );
}

List_point create_empty_point() {
    return NULL;
}

int is_empty_point(List_point l) {
    return l == NULL;
}

List_point make_point(Point e, List_point l) {
    List_point res = malloc(sizeof(struct Node_point));
    res->v = e;
    res->next = l;
    return res;
}

void add_point(Point e, List_point *l) {
    *l= make_point(e, *l);}

Point pop_point(List_point *l){
    Point e = (*l)->v;
    List_point nextnode = (*l)->next;
    free(*l);
    (*l)=nextnode;
    return e;
}

void flood_fill(int x, int y, pixel old, pixel new,matrix *m) {
    if((old.c.r==new.c.r) && (old.c.g==new.c.g) && (old.c.b==new.c.b) && (old.op==new.op)){}
    else{
    List_point l = create_empty_point();
    add_point((Point){x,y},&l);
    while (!is_empty_point(l)) { //Fin quand l est vide (l==NULL)
        Point p = pop_point(&l);
        int x = p.x;
        int y = p.y;
        if ((m->cells[x][y].c.r == old.c.r) && (m->cells[x][y].c.g == old.c.g) && (m->cells[x][y].c.b== old.c.b) && (m->cells[x][y].op == old.op) ){
            m->cells[x][y] = new;
            if (is_valid(x + 1,y,m->size)) {add_point((Point){x + 1,y},&l);}
            if (is_valid(x - 1,y,m->size)) {add_point((Point){x - 1,y},&l);}
            if (is_valid(x,y + 1,m->size)) {add_point((Point){x,y + 1},&l);}
            if (is_valid(x,y - 1,m->size)) {add_point((Point){x,y - 1},&l);}}
    }
}
} 