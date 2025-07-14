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

void rotacao_esquerda(FILE* f1, FILE* f2){
 PPM image;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval); // lê do ficheiro de entrada(f1) o P3 e as dimensões da imagem e do maxval que é 255.
 fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.height,image.width,image.maxval); // escreve no ficheiro de saida(f2) as informações lidas do ficheiro de entrada

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

for (int j =0; j<image.width; j++){ // imprime os pixeis
 for (int k = image.height-1;k>=0; k--){ //imprime de bauxi para cima, pois vai começar por imprimir a partir da primeira coluna,última linha
 fprintf(f2,"%d ",image.mat[k][j].r);
 fprintf(f2,"%d ", image.mat[k][j].g);
 fprintf(f2,"%d\n",image.mat[k][j].b);
 }
}

 fclose(f2); // fecha o ficheiro de saída
 free(image.mat); // libertar memória
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;

 if(argc > 1){
 f1 = fopen(argv[1], "r"); // lê o ficheiro de entrada

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
 rotacao_esquerda(f1,f2);
 return 0;
}
