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

void moldura(FILE* f1, FILE* f2,int a,PPMPIXEL aux){
   PPM image;
 PPM resultado;

 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
resultado.magicNumber = image.magicNumber;
resultado.width = 2*a+image.width; // a = largura da moldura, mas como quero contar com a extremidade, é duas vezes mais o comprimento
resultado.height = 2*a + image.height; // analogamente ao anterior
resultado.maxval = image.maxval;

fprintf(f2,"P%d\n%d %d\n%d\n",resultado.magicNumber,resultado.width,resultado.height,resultado.maxval); // escreve no ficheiro de saida(f2) as informações lidas do ficheiro de entrada

image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

 for(int i=0;i<image.height;i++){ // alocar memória da imagem
  image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
  for(int j=0;j<image.width;j++){
   PPMPIXEL p;
    fscanf(f1,"%d %d %d",&p.r,&p.g,&p.b);
  image.mat[i][j]=p;
  }
 }
resultado.mat= (PPMPIXEL **) malloc(resultado.height * sizeof(PPMPIXEL *));

 for(int i=0;i<resultado.height;i++){ // mesma coisa para o resultado da imagem obtida
  resultado.mat[i]= (PPMPIXEL *) malloc(resultado.width*sizeof(PPMPIXEL));
 }
 fclose(f1);

 for (int j =0; j<resultado.height; j++){
   for (int k = 0; k < resultado.width; k++){
    if(j<a || k<a || j>resultado.height-1-a || k>resultado.width-1-a){
     // se  a posição da linha,da coluna, for menor que o valor atribuído para a espessura, bem como, se a posição da linha, coluna atual for maior do que a diferença da minha altura,largura-1- o valor atribuído, então faz o que está em baixo.
     resultado.mat[j][k].r=aux.r; // a combinação RGB é imprimida nesse pixel
     resultado.mat[j][k].g=aux.g;
     resultado.mat[j][k].b=aux.b;
  }else{
    resultado.mat[j][k]=image.mat[j-a][k-a]; // caso a condição não seja satisfeita, imprime o que estava na imagem original
  }
 }
 }

  for (int j =0; j<resultado.height; j++){ // imprime os pixeis
   for (int k = 0; k < resultado.width; k++){
   fprintf(f2,"%d ",resultado.mat[j][k].r);
   fprintf(f2,"%d ", resultado.mat[j][k].g);
   fprintf(f2,"%d\n",resultado.mat[j][k].b);
   }
 }


  fclose(f2); // fecha o ficheiro de saída
  free(image.mat); // libertar memória
 }


int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;

 PPMPIXEL aux; // vai buscar os pixeis
 int a;
 a = atoi(argv[1]);  // converte string em inteiro, o argumento que introduzo para a espessura da moldura
aux.r=atoi(argv[2]); // combinação de valores RGB, que vão dar a cor à moldura e vão ser guardados na estrutura
aux.g=atoi(argv[3]);
aux.b=atoi(argv[4]);
 if(argc > 5){
 f1 = fopen(argv[5], "r"); // lê o ficheiro de entrada

 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
}
 }
 else{
   f1= stdin;
 }

 if(argc > 6){
 f2 = fopen(argv[6], "w"); // escreve no ficheiro de saída
 }
 else{
 f2 = stdout;
 }
 moldura(f1,f2,a,aux);
 return 0;
}
