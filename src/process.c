#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

#include "imageprocessing.h"

static float *matriz1;
static float *matriz2;
static float *matriz3;
void processaMatriz(float* baseMatrix ,int width, int height);
static int N;
int main(int argc, char *argv[]){
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Criar area de memoria compartilhada */
    imagem img;
    N = atoi(argv[1]);
    img = abrir_imagem(argv[2]);

    unsigned int somaR = 0, somaG = 0, somaB = 0, quant = 0;

    float alpha = 0.998;
    struct timeval start, stop;
    double secs = 0;

    //Daqui em diante é a forma multithread
    gettimeofday(&start, NULL);
    pid_t p1;
    p1 = fork();
    if (p1 == 0){
	processaMatriz(img.r, img.width, img.height);
        exit(0);
    }

    waitpid(p1, NULL, 0);


    gettimeofday(&stop, NULL);

    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken multi process: %f\n", secs);

    if (argc > 2){
    	salvar_imagem("output-process.jpg", &img);
    }else{
    	salvar_imagem(argv[2],&img);
    }
    liberar_imagem(&img);
    return 0;
}

void processaMatriz(float* baseMatrix ,int width, int height){

        float *matriz = malloc(sizeof(float) * width * height) ;
        memcpy(matriz, baseMatrix,  sizeof(float) * height * width);
		
	int soma = 0, quant = 0;
	for (int i = 0; i < (width); i++){
	    for (int j = 0; j < (height); j++){
		for (int l = j - N; l < j + N; l++){
		    if (l >= 0 && l < height){
			for (int k = i - N; k < i + N; k++){
			    if (k >= 0 && k < width){
				soma = soma + baseMatrix[l * width + k];
				quant++;
			    }
			}
		    }
		}
		matriz[j * width + i] = soma / quant;
		soma = 0;
		quant = 0;
	    }
	}
}
