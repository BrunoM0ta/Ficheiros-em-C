#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void equalizacao(FILE* f1, FILE* f2){
   PPM image,resultado;
   fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
   resultado.magicNumber = image.magicNumber; // precisa de transferir o valor P3 para o ficheiro de output
   resultado.width = image.width;  // precisa de transferir o valor P3 para o ficheiro de output
   resultado.height = image.height; // queremos ajustar as dimensões da nova imagem, ou seja, que vai ser a soma dos comprimentos de image e image1,respetivamente, como no enunciado
  resultado.maxval= image.maxval;
    fscanf(f2,"P%d\n%d %d\n%d\n",&resultado.magicNumber,&resultado.width,&resultado.height,&resultado.maxval);

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

     int acc = 0;
     for(int i=0; i<(image.maxval+1); i++){
       if(histo[i] != 0){
         histo[i] += acc;
         acc = histo[i];
       }
     }
       int cdfMin=-1;
       for(int i=0; (cdfMin = histo[i]) == -1; i++);

     for (int j =0; j<resultado.height; j++){ // começa por analisar a primeira imagem, percorrendo todas as linhas e colunas
     for (int k = 0; k < resultado.width; k++){
       resultado.mat[j][k].r = round((histo[resultado[j][k].r] - cdfMin) * (image.maxval-1) / (image.width * image.height - cdfMin));
}
}
     for (int j =0; j<resultado.height; j++){ // começa por analisar a primeira imagem, percorrendo todas as linhas e colunas
     for (int k = 0; k < resultado.width; k++){
    fprintf(f2,"%d",resultado.mat[j][k].r);
    fprintf(f2,"%d",resultado.mat[j][k].g);
    fprintf(f2,"%d",resultado.mat[j][k].b);
  }
}
fclose(f2);
free(image.mat);

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

equalizacao(f1,f2);
 return 0;
}
