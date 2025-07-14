#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct ppmPixel{ // estrutura que guarda os códigos das cores
 int r,g,b;
};

typedef struct ppmPixel PPMPIXEL;

struct ppmImage{
 int magicNumber;
 int width,height,maxval;
 PPMPIXEL** mat;
};  // estrutura que guarda as dimensões da imagem

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
   //agora vamos trocar os indices
 int mid = image.width / 2; // precisamos de pensar da seguinte maneira: dividir a imagem ao meio, tendo como referencial a altura, de cima até ao meio
  PPMPIXEL a;
 for (int j = 0; j < image.height; j++){
  for (int k = 0; k < mid; k++){ // precorre até ao meio de cima para baixo
  a = image.mat[j][k];
  image.mat[j][k] = image.mat[j][image.width - k - 1];
  image.mat[j][image.width - k - 1] = a; // trocam-se os pixeis, trocando os índices
  }
 }
     //agora imprimimos
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

 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));   //alocar array de linhas

 for(int i=0;i<image.height;i++){
 image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
   //ISTO AQUI LE A IMAGEM
  for(int j=0;j<image.width;j++){
        //alocar linha i
  PPMPIXEL p;
      //lemos os pixeis e guardamos
  fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
  image.mat[i][j]=p;
  }
 }
   //agora vamos trocar os indices
 int mid = image.width / 2;
 PPMPIXEL a;  // guarda o pixel nesta variável
 for (int j = 0; j < image.height; ++j){
  for (int k = 0; k < mid; ++k){
  a = image.mat[j][k];
  image.mat[j][k] = image.mat[j][image.width - k - 1];
  image.mat[j][image.width - k - 1] = a;
  }
 }
 for (int j =0; j<image.height; j++){
  for (int k = 0; k < image.width; ++k){
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
