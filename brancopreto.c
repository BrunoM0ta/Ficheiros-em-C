#include <stdio.h>
#include <stdlib.h>

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

void cinza(FILE* f1, FILE* f2, int referencia){
 PPM image;
 int grey;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval); // lê do ficheiro de entrada(f1) o P3 e as dimensões da imagem e do maxval que é 255.
 fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval); // escreve no ficheiro de saida(f2) as informações lidas do ficheiro de entrada

 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

 for(int i=0;i<image.height;i++){
  image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
  for(int j=0;j<image.width;j++){
  PPMPIXEL p;
  fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);// ler do ficheiro de entrada os pixeis
  image.mat[i][j]=p;
  }
 }
 fclose(f1);
 for (int j =0; j<image.height; j++){
  for (int k = 0; k < image.width; k++){
  grey= 0.2126*image.mat[j][k].r + 0.7152*image.mat[j][k].g + 0.0722*image.mat[j][k].b +0.5;
   // aplicação da fórmula mais 0.5 por causa da truncação
   if(grey > referencia){ // caso o valor calculado é maior que o valor de referência(threshold)
     grey=image.maxval; // o valor de grey assume o valor de MAXCOLOR(255)
   }else{
     grey=0;// senão assume 0
   }
  image.mat[j][k].r=grey;
  image.mat[j][k].g=grey;
  image.mat[j][k].b=grey;
 }
}
 for (int j =0; j<image.height; j++){ // imprime os pixeis
  for (int k = 0; k < image.width; k++){
  printf ("%d ",image.mat[j][k].r);
  printf ("%d ", image.mat[j][k].g);
  printf ("%d\n",image.mat[j][k].b);
  }
 }
 fclose(f2); // fecha o ficheiro de saída
 free(image.mat); // libertar memória
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;
int referencia = atoi(argv[1]);

 if(argc > 2){
 f1 = fopen(argv[2], "r"); // lê o ficheiro de entrada

 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
}
 }
 else{
   f1= stdin;
 }

 if(argc > 3){
 f2 = fopen(argv[3], "w"); // escreve no ficheiro de saída
 }
 else{
 f2 = stdout;
 }
 cinza(f1,f2,referencia);
 return 0;
}
