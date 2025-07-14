#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct ppmPixel{
 int r,g,b;
};

typedef struct ppmPixel PPMPIXEL;

struct ppmImage{
 int magicNumber;
 int width,height,maxval;
 PPMPIXEL** mat;
};

typedef struct ppmImage PPM;

void execute(FILE* f1, FILE* f2){
 if(f1==NULL){
 printf("O ficheiro n existe!");
 exit(1);
 }
 else if(f2==NULL){
 printf("O ficheiro n existe!");
 exit(1);
 }
 PPM image;
 PPMPIXEL a;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
 fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);
 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));
 for(int i=0;i<image.height;i++){
  image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
  for(int j=0;j<image.width;j++){
  PPMPIXEL p;
  fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
  image.mat[i][j]=p;
  }
 }
 int mid = image.width / 2;
 for (int j = 0; j < image.height; j++){ // para produzir a diagonal, basta apenas juntar ambas as transformações, é no fundo, um somatório dos outros dois
  for (int k = 0; k < mid; k++){
  a = image.mat[j][k];
  image.mat[j][k] = image.mat[j][image.width - k - 1]; // transformação horizontal
  image.mat[j][image.width - k - 1] = a;
  }
 }
 int mid1 = image.height / 2;
 for (int j = 0; j < image.width; j++){
  for (int k = 0; k < mid1; k++){
  a = image.mat[k][j];
  image.mat[k][j] = image.mat[image.height-k-1][j]; // transformação vertical
  image.mat[image.height-k-1][j] = a;
  }
 }
 for (int j =0; j<image.height; j++){
  for (int k = 0; k < image.width; k++){
  fprintf (f2,"%d ", image.mat[j][k].r);
  fprintf (f2,"%d ", image.mat[j][k].g);
  fprintf (f2,"%d\n", image.mat[j][k].b);
  }
 }
 fclose(f1);
 fclose(f2);
 free(image.mat);
}

void execute2(FILE* f1){
 PPM image;
 if(f1==NULL){
 printf("O ficheiro n existe!");
 exit(1);
 }
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
 printf("P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);
 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));
 for(int i=0;i<image.height;i++){
 image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
  for(int j=0;j<image.width;j++){
  PPMPIXEL p;
  fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
  image.mat[i][j]=p;
  }
 }
 for (int j = image.height-1; j>=0; j--){ // imprime na forma inversa, da direita para a esquerda , de baixo para cima.
  for (int k = image.width-1; k >=0 ; k--){
  printf ("%d ", image.mat[j][k].r);
  printf ("%d ", image.mat[j][k].g);
  printf ("%d\n", image.mat[j][k].b);
  }
 }
 fclose(f1);
 free(image.mat);
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;
 if(argc==1){
 f1=stdin;
 execute2(f1);
 }
 else if(argc==2){
 f1=fopen(argv[1],"r");
 execute2(f1);
 }
 for(int i=2;i<argc;i++){
 f1=fopen(argv[1],"r");
 f2=fopen(argv[2],"w");
  if(f1==NULL){
  printf(" <file>: No such file or directory");
  getchar();
  exit(1);
  }
    execute(f1,f2);
 }
 return 0;
}
