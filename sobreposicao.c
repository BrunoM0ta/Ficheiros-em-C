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

void justaposicao(FILE* f1, FILE* f2, FILE* f3,int x,int y){ // acrescentou-se mais um argumento (FILE* f3), pois vou precisar de mais um ficheiro de saída
   PPM image,image1,resultado;
 fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval); // precisa de ler o primeiro ficheiro
  fscanf(f2,"P%d\n%d %d\n%d\n",&image1.magicNumber,&image1.width,&image1.height,&image1.maxval); // e , semelhantemente, o segundo
resultado.magicNumber = image.magicNumber;
resultado.width = image1.width;
resultado.height = image1.height;
resultado.maxval = image.maxval; // precisa de transferir o valor máximo 255 para a nova imagem
 fprintf(f3,"P%d\n%d %d\n%d\n",resultado.magicNumber,resultado.width,resultado.height,resultado.maxval); // imprime os parâmetros no novo ficheiro
image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *)); // alocar a memória dinamicamente

for(int i=0;i<image.height;i++){ // alocar memória da imagem
  image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
  PPMPIXEL p;
fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);// ler do ficheiro de entrada os pixeis
image.mat[i][j]=p;
}
}

image1.mat= (PPMPIXEL **) malloc(image1.height * sizeof(PPMPIXEL *)); // alocar a memória da segunda imagem

 for(int i=0;i<image1.height;i++){ // alocar memória da imagem
  image1.mat[i]= (PPMPIXEL *) malloc(image1.width*sizeof(PPMPIXEL));
    for(int j=0;j<image1.width;j++){
      PPMPIXEL g;
fscanf(f2,"%d %d %d\n",&g.r, &g.g,&g.b);// ler do ficheiro de entrada os pixeis
image1.mat[i][j]=g;
}
}

resultado.mat= (PPMPIXEL **) malloc(resultado.height * sizeof(PPMPIXEL *));

 for(int i=0;i<resultado.height;i++){ // mesma coisa para o resultado da imagem obtida
  resultado.mat[i]= (PPMPIXEL *) malloc(resultado.width*sizeof(PPMPIXEL));
 }

 fclose(f1); // fecha os dois ficheiros
 fclose(f2);

 for (int j =0; j<image1.height; j++){ // começa por analisar a segunda imagem, percorrendo todas as linhas e colunas
 for (int k = 0; k < image1.width; k++){
 resultado.mat[j][k].r=image1.mat[j][k].r; // transfere os valores dos pixeis da segunda imagem para resultado, o novo ficheiro, vai receber estes valores
 resultado.mat[j][k].g=image1.mat[j][k].g;
 resultado.mat[j][k].b=image1.mat[j][k].b;
}
}

for (int j =y,m=0; j<image1.height && m<image.height; j++,m++){ // aqui é preciso inserir a primeira imagem(no enunciado, clock.ppm), a partir da posição x e y da segunda imagem, que vai percorrer as restantes lnihas desta última
 for (int k = x,n=0; k < image1.width && n<image.width; k++,n++){ // a mesma coisa para as colunas
   resultado.mat[j][k].r=image.mat[m][n].r; // aqui é necessário que os índices da primeira imagem partam da origem
   resultado.mat[j][k].g=image.mat[m][n].g;
   resultado.mat[j][k].b=image.mat[m][n].b;
}
}

for (int j =0; j<resultado.height; j++){ // imprime os pixeis no novo ficheiro f3
 for (int k = 0; k < resultado.width; k++){
 fprintf(f3,"%d ",resultado.mat[j][k].r);
 fprintf(f3,"%d ", resultado.mat[j][k].g);
 fprintf(f3,"%d\n",resultado.mat[j][k].b);
 }
}

// fecha o ficheiro de saída
fclose(f3);
free(image.mat); // libertar memória
free(image1.mat);
}

int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;
 FILE* f3;
int x,y;
 x=atoi(argv[1]);
 y=atoi(argv[2]);

 if(argc > 3){
 f1 = fopen(argv[3], "r"); // lê a primeira imagem

 if(f1 == NULL){
 printf(" <file>: No such file or directory");
 exit(1);
}
 }
 else{
   f1= stdin;
 }

 if(argc > 4){
 f2 = fopen(argv[4], "r"); // lê a segunda imagem

if(f2==NULL){
 printf(" <file>: No such file or directory");
 exit(1);
 }
}
 else{
 f2 = stdin;
 }

 if(argc > 5){
 f3 = fopen(argv[5], "w"); // escreve no ficheiro de saída
 }
 else{
 f3 = stdout;
 }

justaposicao(f1,f2,f3,x,y);
 return 0;
}
