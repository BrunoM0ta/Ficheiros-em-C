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


void locais(FILE* f1,FILE* f2){
PPM image;
 PPM resultado;

fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
resultado.magicNumber = image.magicNumber;
resultado.width = image.width; // a = largura da moldura, mas como quero contar com a extremidade, é duas vezes mais o comprimento
resultado.height = image.height; // analogamente ao anterior
resultado.maxval = image.maxval;
fprintf(f2,"P%d\n%d %d\n%d\n",resultado.magicNumber,resultado.width,resultado.height,resultado.maxval);

image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

for(int i=0;i<image.height;i++){ // alocar memória da imagem
 image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
   for(int j=0;j<image.width;j++){
     PPMPIXEL g;
fscanf(f1,"%d %d %d\n",&g.r, &g.g,&g.b);// ler do ficheiro de entrada os pixeis
image.mat[i][j]=g;
}
}

resultado.mat= (PPMPIXEL **) malloc(resultado.height * sizeof(PPMPIXEL *));

 for(int i=0;i<resultado.height;i++){ // mesma coisa para o resultado da imagem obtida
  resultado.mat[i]= (PPMPIXEL *) malloc(resultado.width*sizeof(PPMPIXEL));
 }
  fclose(f1);

 for (int j =0; j<image.height; j++){
  for (int k = 0; k < image.width; k++){
    if(j==0 || k==0 || j==image.height-1 || k==image.width-1){
  resultado.mat[j][k].r=image.mat[j][k].r;
  resultado.mat[j][k].g=image.mat[j][k].g;
  resultado.mat[j][k].b=image.mat[j][k].b;
}else if((image.mat[j][k].r > image.mat[j][k-1].r)&& (image.mat[j][k].r > image.mat[j-1][k].r) && (image.mat[j][k].r > image.mat[j-1][k-1].r) && (image.mat[j][k].r > image.mat[j+1][k+1].r) && (image.mat[j][k].r > image.mat[j+1][k-1].r) && (image.mat[j][k].r > image.mat[j-1][k+1].r) && (image.mat[j][k].r > image.mat[j+1][k].r) && (image.mat[j][k].r > image.mat[j][k+1].r)){
    resultado.mat[j][k].r=image.maxval;
   resultado.mat[j][k].g=0;
   resultado.mat[j][k].b=0;
 }else{
     resultado.mat[j][k].r=image.mat[j][k].r;
     resultado.mat[j][k].g=image.mat[j][k].g;
     resultado.mat[j][k].b=image.mat[j][k].b;
   }
 }
}
for (int j =0; j<image.height; j++){
 for (int k = 0; k < image.width; k++){
   fprintf(f2,"%d ",resultado.mat[j][k].r);
   fprintf(f2,"%d ",resultado.mat[j][k].g);
   fprintf(f2,"%d\n",resultado.mat[j][k].b);
}
}
fclose(f2);
free(image.mat);
free(resultado.mat);
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;

 if(argc > 1){
 f1 = fopen(argv[1], "r"); // lê a primeira imagem

 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
}
 }
 else{
   f1= stdin;
 }


 if(argc > 2){
 f2 = fopen(argv[2], "w"); // escreve no ficheiro de saída
 }
 else{
 f2 = stdout;
 }

locais(f1,f2);
 return 0;
}
