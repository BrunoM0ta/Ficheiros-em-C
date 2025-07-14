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

void rgb(FILE* f1, FILE* f2, int r, int g, int b){
 PPM image;
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
  image.mat[j][k].r = image.mat[j][k].r + r;// soma o pixel do vermelho com o parâmetro que está no argumento da linha de comandos 1
  image.mat[j][k].g = image.mat[j][k].g + g; // soma o pixel do verde com o parâmetro que está no argumento da linha de comandos 2
  image.mat[j][k].b = image.mat[j][k].b + b; // soma o pixel do azul com o parâmetro que está no argumento d alinha de comandos 3

  if (image.mat[j][k].r > 255){ // se a soma for superior que 255 mantém o valor padrão,neste caso,255.
  image.mat[j][k].r=255;
}else  if (image.mat[j][k].r < 0){ // se a soma for inferior a 0, mantém este valor
  image.mat[j][k].r=0;
}

  if (image.mat[j][k].g > 255){ // semenlhante ao anteiror
  image.mat[j][k].g=255;
}else if (image.mat[j][k].g < 0){
  image.mat[j][k].g=0;
}


  if (image.mat[j][k].b > 255){ // semenlhante ao anteiror
  image.mat[j][k].b=255;
}else if (image.mat[j][k].b < 0){
  image.mat[j][k].b=0;
}
  }

 }
 for (int j =0; j<image.height; j++){ // imprime os pixeis
  for (int k = 0; k < image.width; k++){
  printf ("%d ", image.mat[j][k].r);
  printf ("%d ", image.mat[j][k].g);
  printf ("%d\n", image.mat[j][k].b);
  }
 }
 fclose(f2); // fecha o ficheiro de saída
 free(image.mat);
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;
 int r,g,b;
 r=atoi(argv[1]); // converte o parâmetro introduzido no argumento de comandos 1 em inteiro
 g=atoi(argv[2]); // converte o parâmetro introduzido no argumento de comandos 2 em inteiro
 b=atoi(argv[3]); // converte o parâmetro introduzido no argumento de comandos 3 em inteiro
 if(argc > 4){
 f1 = fopen(argv[4], "r");
 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
 }
 if(argc > 5){
 f2 = fopen(argv[5], "w");
 }
 else{
 f2 = stdout;
 }
 }
 else{
 f1 = stdin;
 f2 = stdout;
 }
 rgb(f1,f2,r,g,b);
 return 0;
}
