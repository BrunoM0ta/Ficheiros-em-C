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

void correpresentada(FILE* f1, FILE* f2){
 PPM image;
 PPM resultado;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
 resultado.magicNumber= image.magicNumber;
 resultado.width= image.width;
 resultado.height= image.height;
 resultado.maxval= image.maxval;
 fprintf(f2,"P%d\n%d %d\n%d\n",resultado.magicNumber,resultado.width,resultado.height,resultado.maxval); // escreve no ficheiro de saida(f2) as informações lidas do ficheiro de entrada

 image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

 for(int i=0;i<image.height;i++){
  image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
  for(int j=0;j<image.width;j++){
  PPMPIXEL p;
  fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);// ler do ficheiro de entrada os pixeis
  image.mat[i][j]=p;
  }
 }

 resultado.mat= (PPMPIXEL **) malloc(resultado.height * sizeof(PPMPIXEL *));

  for(int i=0;i<resultado.height;i++){ // mesma coisa para o resultado da imagem obtida
   resultado.mat[i]= (PPMPIXEL *) malloc(resultado.width*sizeof(PPMPIXEL));
  }

 fclose(f1);
int soma_vermelho=0;
int soma_verde=0;
int soma_azul=0;
int mediavermelho;
int mediaverde;
int mediazul;
int nvermelho=0;
int nverde=0;
int nazul=0;
 for (int j =0; j<resultado.height; j++){
  for (int k = 0; k < resultado.width; k++){
  resultado.mat[j][k].r = image.mat[j][k].r;
  resultado.mat[j][k].g = image.mat[j][k].g;
  resultado.mat[j][k].b = image.mat[j][k].b;
soma_vermelho+=image.mat[j][k].r;
soma_verde+=image.mat[j][k].g;
soma_azul+=image.mat[j][k].b;
nvermelho++;
nverde++;
nazul++;
  }

 }

 mediavermelho=soma_vermelho/nvermelho;
 mediaverde=soma_verde/nverde;
 mediazul=soma_azul/nazul;
int maximo;
 if(mediavermelho>mediaverde){
   maximo=mediavermelho;
 }else if(mediavermelho<mediaverde){
   maximo=mediaverde;
 }

 if(maximo<mediazul){
   maximo=mediazul;
 }else{
   maximo=maximo;
 }


 for (int j =0; j<resultado.height; j++){
  for (int k = 0; k < resultado.width; k++){

  if(maximo==mediavermelho){
    resultado.mat[j][k].r= image.mat[j][k].r;
    resultado.mat[j][k].g= 0;
    resultado.mat[j][k].b=0;
  }else if(maximo==mediaverde){
    resultado.mat[j][k].r= 0;
    resultado.mat[j][k].g=image.mat[j][k].g;
    resultado.mat[j][k].b=0;
  }else{
    resultado.mat[j][k].r= 0;
    resultado.mat[j][k].g=0;
    resultado.mat[j][k].b=image.mat[j][k].b;
  }

  }
}

 for (int j =0; j<resultado.height; j++){ // imprime os pixeis
  for (int k = 0; k < resultado.width; k++){
  fprintf (f2,"%d ", resultado.mat[j][k].r);
  fprintf (f2,"%d ", resultado.mat[j][k].g);
  fprintf (f2,"%d\n", resultado.mat[j][k].b);
  }
 }
 fclose(f2); // fecha o ficheiro de saída
 free(image.mat);
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;

 if(argc > 1){
 f1 = fopen(argv[1], "r");
 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
 }
 if(argc > 2){
 f2 = fopen(argv[2], "w");
 }
 else{
 f2 = stdout;
 }
 }
 else{
 f1 = stdin;
 f2 = stdout;
 }
 correpresentada(f1,f2);
 return 0;
}
