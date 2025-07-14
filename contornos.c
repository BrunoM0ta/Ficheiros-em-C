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

void contorno(FILE* f1, FILE* f2){
 PPM image;
 PPM resultado;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
 resultado.magicNumber= image.magicNumber;
 resultado.width= image.width;
 resultado.height= image.height;
 resultado.maxval= image.maxval; // lê do ficheiro de entrada(f1) o P3 e as dimensões da imagem e do maxval que é 255.
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

 for (int j =0; j<image.height; j++){
  for (int k = 0; k < image.width; k++){
    if(j==0 || k==0 || j==image.height-1 || k==image.width-1){
      resultado.mat[j][k].r=0;
      resultado.mat[j][k].g=0;
      resultado.mat[j][k].b=0;
    }else{
      resultado.mat[j][k].r=8*image.mat[j][k].r-(image.mat[j-1][k-1].r+image.mat[j-1][k].r+image.mat[j][k-1].r+image.mat[j+1][k-1].r+image.mat[j+1][k+1].r+image.mat[j-1][k+1].r+image.mat[j][k+1].r+image.mat[j+1][k].r);
      resultado.mat[j][k].g=8*image.mat[j][k].g-(image.mat[j-1][k-1].g+image.mat[j-1][k].g+image.mat[j][k-1].g+image.mat[j+1][k-1].g+image.mat[j+1][k+1].g+image.mat[j-1][k+1].g+image.mat[j][k+1].g+image.mat[j+1][k].g);
      resultado.mat[j][k].b=8*image.mat[j][k].b-(image.mat[j-1][k-1].b+image.mat[j-1][k].b+image.mat[j][k-1].b+image.mat[j+1][k-1].b+image.mat[j+1][k+1].b+image.mat[j-1][k+1].b+image.mat[j][k+1].b+image.mat[j+1][k].b);
     if(image.mat[j][k].r<0){
        resultado.mat[j][k].r=0;
        resultado.mat[j][k].g=0;
        resultado.mat[j][k].b=0;
      }else if(image.mat[j][k].r>image.maxval){
        resultado.mat[j][k].r=image.maxval;
          resultado.mat[j][k].g=image.maxval;
            resultado.mat[j][k].b=image.maxval;
      }
   }

      }
    }
      for (int j =0; j<resultado.height; j++){
       for (int k = 0; k < resultado.width; k++){
         fprintf (f2,"%d ",resultado.mat[j][k].r);
         fprintf (f2,"%d ", resultado.mat[j][k].g);
         fprintf (f2,"%d ",resultado.mat[j][k].b);
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
        contorno(f1,f2);
        return 0;
       }
