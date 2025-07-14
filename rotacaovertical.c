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


void horizontal1(FILE* f1,FILE* f2){
  if(f1==NULL){
printf("O ficheiro n existe!");
exit(1);
}
else if(f2==NULL){
printf("O ficheiro n existe!");
exit(1);
}
  PPM image;
   fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
   fprintf(f2,"P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

   image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

   for(int i=0;i<image.height;i++){
    image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
    PPMPIXEL p;
    fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
    image.mat[i][j]=p;
    }
   }
   int meio = image.height /2;
   PPMPIXEL a;
   for(int j=0;j<image.width;j++){
     for(int k=0;k<meio;k++){
         a=image.mat[k][j];
         image.mat[k][j]= image.mat[image.height-k-1][j];
         image.mat[image.height-k-1][j]=a;
     }
   }

   for(int j=0;j<image.height;j++){
     for(int k=0;k<image.width;k++){
  fprintf(f2,"%d",image.mat[j][k].r);
  fprintf(f2,"%d",image.mat[j][k].g);
  fprintf(f2,"%d\n",image.mat[j][k].b);
}
}
fclose(f1);
fclose(f2);
free(image.mat);

}

void horizontal2(FILE* f1){
  if(f1==NULL){
printf("O ficheiro n existe!");
exit(1);
}
  PPM image;
   fscanf(f1,"P%d\n%d %d\n%d\n",&image.magicNumber,&image.width,&image.height,&image.maxval);
   printf("P%d\n%d %d\n%d\n",image.magicNumber,image.width,image.height,image.maxval);

   image.mat= (PPMPIXEL **) malloc(image.height * sizeof(PPMPIXEL *));

   for(int i=0;i<image.height;i++){
    image.mat[i]= (PPMPIXEL *) malloc(image.width*sizeof(PPMPIXEL));
    for(int j=0;j<image.width;j++){
    PPMPIXEL p;
    fscanf(f1,"%d %d %d\n",&p.r, &p.g,&p.b);
    image.mat[i][j]=p;
    }
   }
   int meio = image.height /2;
   PPMPIXEL a;
   for(int j=0;j<image.width;j++){
     for(int k=0;k<meio;k++){
         a=image.mat[k][j];
         image.mat[k][j]= image.mat[image.height-k-1][j];
         image.mat[image.height-k-1][j]=a;
     }
   }

   for(int j=0;j<image.height;j++){
     for(int k=0;k<image.width;k++){
  printf("%d",image.mat[j][k].r);
  printf("%d",image.mat[j][k].g);
  printf("%d\n",image.mat[j][k].b);
}
}
fclose(f1);
free(image.mat);

}





int main(int argc, char* argv[]){
 FILE* f1;
 FILE* f2;

 if(argc==1){
 f1=stdin;
vertical2(f1);
 }
 else if(argc==2){
 f1=fopen(argv[1],"r");
 vertical2(f1);
 }
 for(int i=2;i<argc;i++){
 f1=fopen(argv[1],"r");
 f2=fopen(argv[2],"w");
  if(f1==NULL){
  printf(" <file>: No such file or directory");
  getchar();
  exit(1);
  }
    vertical1(f1,f2);

 return 0;
}
