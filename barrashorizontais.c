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

void barrashorizontais(FILE* f1, FILE* f2,int espessura,PPMPIXEL aux){
   PPM image;
 PPM resultado;

 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
 // valores da imagem final(P3, dimensões e valor máximo)
resultado.magicNumber = image.magicNumber;
resultado.width = image.width; // a = largura da moldura, mas como quero contar com a extremidade, é duas vezes mais o comprimento
resultado.height = image.height; // analogamente ao anterior
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
    if(((k+espessura) % (espessura*2)) < espessura) {
     resultado.mat[j][k].r= aux.r;
     resultado.mat[j][k].g= aux.g;
     resultado.mat[j][k].b= aux.b;
    }
    else {
     resultado.mat[j][k].r= image.mat[j][k].r;
     resultado.mat[j][k].g= image.mat[j][k].g;
     resultado.mat[j][k].b= image.mat[j][k].b;
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
 int espessura;
 espessura = atoi(argv[1]);  // converte string em inteiro, o argumento que introduzo para a espessura da moldura
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
barrashorizontais(f1,f2,espessura,aux);
 return 0;
}
