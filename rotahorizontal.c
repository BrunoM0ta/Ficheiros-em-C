#include <stdio.h>
#include <stdlib.h>

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

void horizontal(FILE* f1,FILE* f2){

  PPM image;
   fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
   fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

   image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *)); // alocar a memória dinamicamente

   for(int i=0;i<image.height;i++){ // alocar memória da imagem
     image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
       for(int j=0;j<image.width;j++){
     PPMPIXEL p;
   fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);// ler do ficheiro de entrada os pixeis
   image.mat[i][j]=p;
   }
   }
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

horizontal(f1,f2);
 return 0;
}
