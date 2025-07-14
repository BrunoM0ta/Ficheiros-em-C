#include<stdio.h>
#include<stdlib.h>

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

void rgb(FILE* f1,FILE* f2,int r, int g, int b){

  PPM image;
  fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
  fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

  for(int i=0;i<image.height;i++){ // alocar memória da imagem
   image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
     for(int j=0;j<image.width;j++){
       PPMPIXEL g;
  fscanf(f1,"%d %d %d\n",&g.r, &g.g,&g.b);// ler do ficheiro de entrada os pixeis
  image.mat[i][j]=g;
  }
  }
  fclose(f1);

  for(int j=0;j<image.height;j++){
    for(int k=0;k<image.width;k++){
      image.mat[j][k].r=image.mat[j][k].r+r;
  image.mat[j][k].g=image.mat[j][k].g+g;
    image.mat[j][k].r=image.mat[j][k].r+r;

if(image.mat[j][k].r<0){
  image.mat[j][k].r=0;
}else if(image.mat[j][k].r>image.maxval){
  image.mat[j][k].r=image.maxval;
}

if(image.mat[j][k].g<0){
  image.mat[j][k].g=0;
}else if(image.mat[j][k].g>image.maxval){
  image.mat[j][k].g=image.maxval;
}

if(image.mat[j][k].b<0){
  image.mat[j][k].b=0;
}else if(image.mat[j][k].b>image.maxval){
  image.mat[j][k].b=image.maxval;
}




}


int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;
 PPMPIXEl aux;
 int r= atoi(argv[1]);
  int g= atoi(argv[2]);
   int b= atoi(argv[3]);
 if(argc > 4){
 f1 = fopen(argv[4], "r"); // lê a primeira imagem

 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
}
 }
 else{
   f1= stdin;
 }


 if(argc > 5){
 f2 = fopen(argv[5], "w"); // escreve no ficheiro de saída
 }
 else{
 f2 = stdout;
 }

rgb(f1,f2);
 return 0;
}
