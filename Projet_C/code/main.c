#include "engine.h"

int main ( int argc, char ** argv ){
    FILE *f;
    if(argc == 3){
        f = fopen(argv[1],"r");//On ouvre le fichier en lecture uniquement
        if(f==NULL){
            fprintf(stderr,"can't open the file\n");
            exit(1);}} 
    if(argc == 2){
        f = fopen(argv[1],"r");//On ouvre le fichier en lecture uniquement
        if(f==NULL){
            fprintf(stderr,"can't open the file\n");
            exit(2);}} 
    if(argc == 1){f = stdin;}
    if(argc!=1 && argc !=2 && argc != 3){
        fprintf(stderr,"wrong number of arguments\n");
        exit(3);}
    char * buff = (char *) malloc( 256 );
    int size;
    fscanf(f,"%d",&size); //On récupère la taille de l'image à créer
    engine e = initialize_engine(size);
    char l=0;
    while ((l = getc(f)) != EOF){ //Fin de boucle à la fin du fichier (getc renvoie EOF)
            switch(l){
                case 'n':
                    add_color_black_in_the_bucket(&e.bucket_color);
                    break;
                case 'r':
                    add_color_red_in_the_bucket(&e.bucket_color);
                    break;
                case 'g':
                    add_color_green_in_the_bucket(&e.bucket_color);
                    break;
                case 'b':
                    add_color_blue_in_the_bucket(&e.bucket_color);
                    break;
                case 'y':
                    add_color_yellow_in_the_bucket(&e.bucket_color);
                    break;
                case 'm':
                    add_color_magenta_in_the_bucket(&e.bucket_color);
                    break;
                case 'c':
                    add_color_cyan_in_the_bucket(&e.bucket_color);
                    break;
                case 'w':
                    add_color_white_in_the_bucket(&e.bucket_color);
                    break;
                case 't':
                    add_opacity_min(&e.bucket_opacity);
                    break;
                case 'o':
                    add_opacity_max(&e.bucket_opacity);
                    break;
                case 'i':
                    empty_bucket_op(&e.bucket_opacity);
                    empty_bucket(&e.bucket_color);
                    break;
                case 'v':
                    go_forward(&e);
                    break;
                case 'h':
                    turn_right(&e);
                    break;
                case 'a':
                    turn_left(&e);
                    break;
                case 'p':
                    position_marked(&e);
                    break;
                case 'l':
                    line_trace(&e);
                    break;
                case 'f':
                    pixel p = current_pixel(e.bucket_opacity,e.bucket_color);
                    flood_fill(e.x,e.y,e.layers.stack[e.layers.top].cells[e.x][e.y],p,&e.layers.stack[e.layers.top]);
                    break;
                case 's':
                    matrix m = matrix_create(size);
                    stack_add_new_layer(m,&e.layers);
                    break;
                case 'e':
                    fusion_layer_final(&e);
                    break;
                case 'j':
                    cut_layer_final(&e);
                    break;
                default:
                    break;

            }
    }
    empty_bucket(&e.bucket_color); //on vide les sceaux (tout en libérant la mémoire) pour éviter les fuites mémoires
    empty_bucket_op(&e.bucket_opacity);
    free(buff); //on libère le buffer pour éviter les fuites mémoire
    if(argc==3){
        fclose(f);
        FILE *fp = fopen(argv[2],"ab+");
        fprintf(fp,"P6\n%d %d\n255\n",size,size);
        for(int i =0; i<size; i++){
            for(int j = 0; j<size; j++){
                fprintf(fp,"%c%c%c",e.layers.stack[e.layers.top].cells[i][j].c.r,e.layers.stack[e.layers.top].cells[i][j].c.g,e.layers.stack[e.layers.top].cells[i][j].c.b);
            }
        }   
        fclose(fp);}
    else{
        FILE *fp = stdout;
        fprintf(fp,"P6\n%d %d\n255\n",size,size);
        for(int i =0; i<size; i++){
            for(int j = 0; j<size; j++){
                fprintf(fp,"%c%c%c",e.layers.stack[e.layers.top].cells[i][j].c.r,e.layers.stack[e.layers.top].cells[i][j].c.g,e.layers.stack[e.layers.top].cells[i][j].c.b);
            }
        }
    }
    free_layers(&e.layers);
    return 0;

}