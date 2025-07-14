#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

typedef struct {
    int red;
    int green;
    int blue;
} Pixel;

typedef struct {
    int magic_number;
    int lines;
    int columns;
    int max_value;
    Pixel** data;
} PPM_Image;

void printFile(char *str){
    FILE *f=fopen(str, "r");
    char c = fgetc(f);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f);
    }
    fclose(f);
}

FILE* openFile(char* s, char *operation){  
    FILE* res;
    res=fopen(s, operation);
    if (res == NULL) exit(2);
    else return res;
}

void printStruct(PPM_Image image, FILE *output){
    fprintf(output, "P%d\n", image.magic_number);  
    fprintf(output, "%d ", image.columns);
    fprintf(output, "%d\n", image.lines); 
    fprintf(output, "%d\n", image.max_value); 
    for(int i=0; i<image.lines; i++){
        for(int j=0; j<image.columns; j++){
           fprintf(output, "%d %d %d\n", image.data[i][j].red, image.data[i][j].green, image.data[i][j].blue);
        }
    }
    fclose(output);
}

int charToInt(char *num){
    int numInt;
    sscanf(num, "%d", &numInt);
    return numInt;
}

int nextNumber(FILE *f){
    char number[MAX]={'\0'}, comments[MAX], ch;
    ch=fgetc(f); 
    while(!(ch >= '0' && ch<='9')){
        if(ch=='#') fgets(comments, MAX, f);
        ch=fgetc(f);
    }
    for(int i=0; ch >= '0' && ch <= '9'; i++){
        if(ch >= '0' && ch<='9') number[i]=ch;
        ch=fgetc(f);
    }
    return charToInt(number);
}

PPM_Image createStruct(FILE *img){
    PPM_Image imgStruct;
    imgStruct.magic_number=nextNumber(img);
    imgStruct.columns=nextNumber(img); 
    imgStruct.lines=nextNumber(img);
    imgStruct.max_value=nextNumber(img);
    imgStruct.data = (Pixel **)malloc(imgStruct.lines * sizeof(Pixel*));
    for (int i = 0; i < imgStruct.lines; ++i) {
        imgStruct.data[i] = (Pixel *)malloc(imgStruct.columns * sizeof(Pixel));
    }
    for(int i=0; i<imgStruct.lines; i++){
        for(int j=0; j<imgStruct.columns; j++){
            imgStruct.data[i][j].red=nextNumber(img);
            imgStruct.data[i][j].green=nextNumber(img);
            imgStruct.data[i][j].blue=nextNumber(img);
        }
    }
    fclose(img);
    return imgStruct;
}

void ppm_h_flip(PPM_Image image, FILE *output){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0, line=0; i<image.lines; i++, line++){
        for(int j=image.columns-1, column=0; j>=0; j--, column++){
            imgRes.data[line][column].red=image.data[i][j].red;
            imgRes.data[line][column].green=image.data[i][j].green;
            imgRes.data[line][column].blue=image.data[i][j].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_v_flip(PPM_Image image, FILE *output){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=image.lines-1, line=0; i>=0; i--, line++){
        for(int j=0, column=0; j<image.columns; j++, column++){
            imgRes.data[line][column].red=image.data[i][j].red;
            imgRes.data[line][column].green=image.data[i][j].green;
            imgRes.data[line][column].blue=image.data[i][j].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_d_flip(PPM_Image image, FILE *output){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=image.lines-1, line=0; i>=0; i--, line++){
        for(int j=image.columns-1, column=0; j>=0; j--, column++){
            imgRes.data[line][column].red=image.data[i][j].red;
            imgRes.data[line][column].green=image.data[i][j].green;
            imgRes.data[line][column].blue=image.data[i][j].blue;
        }
    }
    printStruct(imgRes, output);
}
int RGBsum(int mod_color, int maxvalue){
    if(mod_color>=maxvalue) return maxvalue;
    else if(mod_color<=0) return 0;
    else return mod_color;
}

void ppm_addRGB(PPM_Image image, FILE *output, int dR, int dG, int dB){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0; i<image.lines; i++){
        for(int j=0; j<image.columns; j++){
            imgRes.data[i][j].red=RGBsum(image.data[i][j].red+dR, image.max_value);
            imgRes.data[i][j].green=RGBsum(image.data[i][j].green+dG, image.max_value);
            imgRes.data[i][j].blue=RGBsum(image.data[i][j].blue+dB, image.max_value);
        }
    }
    printStruct(imgRes, output);
}

void addRGBMain(int argc, char *argv[], int dR, int dG, int dB){
    FILE *fileInput, *fileOutput;
    switch(argc){
        case 4:
            fileInput=stdin;
            fileOutput=stdout;
            ppm_addRGB(createStruct(fileInput), fileOutput, dR, dG, dB);
            break;
        case 5:
            fileInput=openFile(argv[4], "r");
            fileOutput=stdout;
            ppm_addRGB(createStruct(fileInput), fileOutput, dR, dG, dB);
            break;
        case 6:
            fileInput=openFile(argv[4], "r");
            fileOutput=openFile(argv[5], "w");
            ppm_addRGB(createStruct(fileInput), fileOutput, dR, dG, dB);
            break;
    }
}

int grayRGB(int red, int green, int blue){
    return round(red*0.2126 + green*0.7152 + blue*0.0722);
}

void ppm_grayscale(PPM_Image image, FILE *output){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0; i<image.lines; i++){
        for(int j=0; j<image.columns; j++){
            int gray=grayRGB(image.data[i][j].red, image.data[i][j].green, image.data[i][j].blue);
            imgRes.data[i][j].red=gray;
            imgRes.data[i][j].green=gray;
            imgRes.data[i][j].blue=gray;
        }
    }
    printStruct(imgRes, output);
}

int thresholdVerifier(int gray, int threshold){
    if(gray>threshold) return 255;
    else return 0;
}

void ppm_bw(PPM_Image image, FILE *output, int threshold){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0; i<image.lines; i++){
        for(int j=0; j<image.columns; j++){
            int newColor=thresholdVerifier(grayRGB(image.data[i][j].red, image.data[i][j].green, image.data[i][j].blue), threshold);
            imgRes.data[i][j].red=newColor;
            imgRes.data[i][j].green=newColor;
            imgRes.data[i][j].blue=newColor;
        }
    }
    printStruct(imgRes, output);
}

void bwMain(int argc, char *argv[], int threshold){
    FILE *fileInput, *fileOutput;
    switch(argc){
        case 2:
            fileInput=stdin;
            fileOutput=stdout;
            ppm_bw(createStruct(fileInput), fileOutput, threshold);
            break;
        case 3:
            fileInput=openFile(argv[2], "r");
            fileOutput=stdout;
            ppm_bw(createStruct(fileInput), fileOutput, threshold);
            break;
        case 4:
            fileInput=openFile(argv[2], "r");
            fileOutput=openFile(argv[3], "w");
            ppm_bw(createStruct(fileInput), fileOutput, threshold);
            break;
    }
}

void ppm_rot_left(PPM_Image image, FILE* output){
    PPM_Image imgRes=image;
    imgRes.lines=image.columns;
    imgRes.columns=image.lines;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
     for(int i=0, l=image.columns-1; i<imgRes.lines; i++, l--){
        for(int j=0; j<imgRes.columns; j++){
            imgRes.data[i][j].red=image.data[j][l].red;
            imgRes.data[i][j].green=image.data[j][l].green;
            imgRes.data[i][j].blue=image.data[j][l].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_rot_right(PPM_Image image, FILE* output){
    PPM_Image imgRes=image;
    imgRes.lines=image.columns;
    imgRes.columns=image.lines;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
     for(int i=0; i<imgRes.lines; i++){
        for(int j=0, k=imgRes.columns-1; j<imgRes.columns; j++, k--){
            imgRes.data[i][j].red=image.data[k][i].red;
            imgRes.data[i][j].green=image.data[k][i].green;
            imgRes.data[i][j].blue=image.data[k][i].blue;
        }
    }
    printStruct(imgRes, output);
}

void addBorder(PPM_Image image, FILE* output, int numPixels, Pixel moldura){
    PPM_Image imgRes=image;
    imgRes.lines=image.lines+(2*numPixels);
    imgRes.columns=image.columns+(2*numPixels);
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0, l=numPixels; i<image.lines; i++, l++){
        for(int j=0, k=numPixels; j<image.columns; j++, k++){
            imgRes.data[l][k].red=image.data[i][j].red;
            imgRes.data[l][k].green=image.data[i][j].green;
            imgRes.data[l][k].blue=image.data[i][j].blue;
        }
    }
    for(int i=0; i<imgRes.lines; i++){
        for(int j=0; j<imgRes.columns; j++){
            if((i<numPixels || j<numPixels) || (i>=numPixels+image.lines || j>=numPixels+image.columns)){
                imgRes.data[i][j].red=moldura.red;
                imgRes.data[i][j].green=moldura.green;
                imgRes.data[i][j].blue=moldura.blue;
            }
        }
    }
    printStruct(imgRes, output);
}

void addBorderMain(int argc, char *argv[], Pixel moldura){
    FILE *fileInput, *fileOutput;
    switch(argc){
        case 5:
            fileInput=stdin;
            fileOutput=stdout;
            addBorder(createStruct(fileInput), fileOutput, charToInt(argv[1]), moldura);
            break;
        case 6:
            fileInput=openFile(argv[5], "r");
            fileOutput=stdout;
            addBorder(createStruct(fileInput), fileOutput, charToInt(argv[1]), moldura);
            break;
        case 7:
            fileInput=openFile(argv[5], "r");
            fileOutput=openFile(argv[6], "w");
            addBorder(createStruct(fileInput), fileOutput, charToInt(argv[1]), moldura);
            break;
    }
}

void ppm_concat(PPM_Image image1, PPM_Image image2, FILE* output){
    PPM_Image imgRes=image1;
    if(image1.lines<image2.lines) imgRes.lines=image1.lines;
    else imgRes.lines=image2.lines;
    imgRes.columns=image1.columns+image2.columns;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int i=0; i<imgRes.lines; i++){
        for(int j=0; j<image1.columns; j++){
            imgRes.data[i][j].red=image1.data[i][j].red;
            imgRes.data[i][j].green=image1.data[i][j].green;
            imgRes.data[i][j].blue=image1.data[i][j].blue;
        }
    }
    for(int i=0; i<imgRes.lines; i++){
        for(int jRes=image1.columns, j2=0; jRes<imgRes.columns; jRes++, j2++){
            imgRes.data[i][jRes].red=image2.data[i][j2].red;
            imgRes.data[i][jRes].green=image2.data[i][j2].green;
            imgRes.data[i][jRes].blue=image2.data[i][j2].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_concatMain(int argc, char *argv[]){
    FILE *fileInput1=openFile(argv[1], "r");
    FILE *fileInput2=openFile(argv[2], "r");
    FILE *fileOutput;
    switch(argc){
        case 3:
            fileOutput=stdout;
            ppm_concat(createStruct(fileInput1), createStruct(fileInput2), fileOutput);
            break;
        default:
            fileOutput=openFile(argv[3], "w");
            ppm_concat(createStruct(fileInput1), createStruct(fileInput2), fileOutput);
            break;
    }
}

void ppm_crop(PPM_Image image, FILE *output, int y1, int x1, int y2, int x2){
    PPM_Image imgRes=image;
    if(x2>=image.lines) imgRes.lines=image.lines-x1;
    else imgRes.lines=x2-x1+1;
    if(y2>=image.columns) imgRes.columns=image.columns-y1;
    else imgRes.columns=y2-y1+1;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    for(int iRes=0, iImg=x1; iRes<imgRes.lines && iImg<image.lines; iRes++, iImg++){
        for(int jRes=0, jImg=y1; jRes<imgRes.columns && jImg<image.columns; jRes++, jImg++){
            imgRes.data[iRes][jRes].red=image.data[iImg][jImg].red;
            imgRes.data[iRes][jRes].green=image.data[iImg][jImg].green;
            imgRes.data[iRes][jRes].blue=image.data[iImg][jImg].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_cropMain(int argc, char *argv[]){
    FILE *fileInput, *fileOutput;
    switch(argc){
        case 5:
            fileInput=stdin;
            fileOutput=stdout;
            ppm_crop(createStruct(fileInput), fileOutput, charToInt(argv[1]),  charToInt(argv[2]),  charToInt(argv[3]),  charToInt(argv[4]));
            break;
        case 6:
            fileInput=openFile(argv[5], "r");
            fileOutput=stdout;
            ppm_crop(createStruct(fileInput), fileOutput, charToInt(argv[1]),  charToInt(argv[2]),  charToInt(argv[3]),  charToInt(argv[4]));
            break;
        default:
            fileInput=openFile(argv[5], "r");
            fileOutput=openFile(argv[6], "w");
            ppm_crop(createStruct(fileInput), fileOutput, charToInt(argv[1]),  charToInt(argv[2]),  charToInt(argv[3]),  charToInt(argv[4]));
            break;
    }
}

void ppm_overlay(PPM_Image overlay, PPM_Image image, FILE *output, int y, int x){
    PPM_Image imgRes=image;
    imgRes.data = (Pixel **)malloc(imgRes.lines * sizeof(Pixel*));
    for(int i = 0; i < imgRes.lines; ++i) {
        imgRes.data[i] = (Pixel *)malloc(imgRes.columns * sizeof(Pixel));
    }
    imgRes=image;
    for(int iRes=x, iOvr=0; iRes<imgRes.lines && iOvr<overlay.lines; iRes++, iOvr++){
        for(int jRes=y, jOvr=0; jRes<imgRes.columns && jOvr<overlay.columns; jRes++, jOvr++){
            imgRes.data[iRes][jRes].red=overlay.data[iOvr][jOvr].red;
            imgRes.data[iRes][jRes].green=overlay.data[iOvr][jOvr].green;
            imgRes.data[iRes][jRes].blue=overlay.data[iOvr][jOvr].blue;
        }
    }
    printStruct(imgRes, output);
}

void ppm_overlayMain(int argc, char *argv[]){
    FILE *fileInput1=openFile(argv[3], "r"), *fileInput2, *fileOutput;
    switch(argc){
        case 4:
            fileInput2=stdin;
            fileOutput=stdout;
            ppm_overlay(createStruct(fileInput1), createStruct(fileInput2), fileOutput, charToInt(argv[1]),  charToInt(argv[2]));
            break;
        case 5:
            fileInput2=openFile(argv[4], "r");
            fileOutput=stdout;
            ppm_overlay(createStruct(fileInput1), createStruct(fileInput2), fileOutput, charToInt(argv[1]),  charToInt(argv[2]));
            break;
        default:
            fileInput2=openFile(argv[4], "r");
            fileOutput=openFile(argv[5], "w");
            ppm_overlay(createStruct(fileInput1), createStruct(fileInput2), fileOutput, charToInt(argv[1]),  charToInt(argv[2]));
            break;
    }
}

void basicOperations(char* operation, FILE *input, FILE *output){
    PPM_Image image = createStruct(input);
    if(strcmp(operation, "./ppm_h_flip_rot")==0){ 
        ppm_h_flip(image, output);
    }
    else if(strcmp(operation, "./ppm_v_flip_rot")==0){
        ppm_v_flip(image, output);
    }
    else if(strcmp(operation, "./ppm_d_flip_rot")==0){
        ppm_d_flip(image, output);
    }
    else if(strcmp(operation, "./ppm_grayscale")==0){
        ppm_grayscale(image, output);
    }
    else if(strcmp(operation, "./ppm_rot_right")==0){
        ppm_rot_right(image, output);
    }
    else if(strcmp(operation, "./ppm_rot_left")==0){
        ppm_rot_left(image, output);
    }
}

int main(int argc, char* argv[]){
    char *operation=argv[0];
    FILE *fileInput, *fileOutput;
    int dR, dG, dB;
    switch(argc){
        case 1:
            fileInput=stdin;
            fileOutput=stdout;
            basicOperations(operation, fileInput, fileOutput);
            break;
        case 2:
            fileInput=openFile(argv[1], "r");
            fileOutput=stdout;
            basicOperations(operation, fileInput, fileOutput);
            break;
        case 3:
            fileInput=openFile(argv[1], "r");
            fileOutput=openFile(argv[2], "w");
            basicOperations(operation, fileInput, fileOutput);
            break;
        default:
        if(strcmp(operation, "./ppm_addRGB")==0){
            dR=charToInt(argv[1]), dG=charToInt(argv[2]), dB=charToInt(argv[3]);
            addRGBMain(argc, argv, dR, dG, dB);
        }
        else if(strcmp(operation, "./ppm_bw")==0){
            bwMain(argc, argv, charToInt(argv[1]));
        }
        else if(strcmp(operation, "./ppm_add_Border")==0){
            Pixel moldura; moldura.red=charToInt(argv[2]); moldura.green=charToInt(argv[3]); moldura.blue=charToInt(argv[4]);
            addBorderMain(argc, argv, moldura);
        }
        else if(strcmp(operation, "./ppm_concat")==0){
            ppm_concatMain(argc, argv); 
        }
        else if(strcmp(operation, "./ppm_crop")==0){
            ppm_cropMain(argc, argv);
        }
        else if(strcmp(operation, "./ppm_overlay")==0){
            ppm_overlayMain(argc, argv);
        }
        break;
    }
    return 0;
}
