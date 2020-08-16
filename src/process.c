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
void processaMatriz(float* baseMatrix , float *matriz, int width, int height);
static int N;

int main(int argc, char *argv[]){
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;
    /* Criar area de memoria compartilhada */
    imagem img;
    N = atoi(argv[1]);
    img = abrir_imagem(argv[2]);

    //criamos as matrizes dos canais de cor com mmap pra poder salvar as mudanças dentro dos processos
    float *matriz_r = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);
    float *matriz_g = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);
    float *matriz_b = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);

    unsigned int somaR = 0, somaG = 0, somaB = 0, quant = 0;

    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);
    //declarando e criando os processos
    pid_t p1,p2,p3;
    p1 = fork();
    p2 = fork();
    p3 = fork();
    if (p1 == 0){
	processaMatriz(img.r, matriz_r ,img.width, img.height);
        exit(0);
    }
    if (p2 == 0){
	processaMatriz(img.g, matriz_g,img.width, img.height);
        exit(0);
    }
    if (p3 == 0){
	processaMatriz(img.b, matriz_b, img.width, img.height);
        exit(0);
    }

    //terminando os processos
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);


    gettimeofday(&stop, NULL);
    
    //atualizando os canais de cor
    img.r = matriz_r;
    img.g = matriz_g;
    img.b = matriz_b;

    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken multi process: %f\n", secs);

    if (argc > 2){
    	salvar_imagem("output-process.jpg", &img);
    }else{
    	salvar_imagem(argv[2],&img);
    }

    //limpando a memoria do mmap
    munmap(img.r, sizeof(float) * img.height * img.width);
    munmap(img.g, sizeof(float) * img.height * img.width);
    munmap(img.b, sizeof(float) * img.height * img.width);
    img.r = NULL;
    img.g = NULL;
    img.b = NULL;

    liberar_imagem(&img);
    return 0;
}

void processaMatriz(float* baseMatrix , float *matriz, int width, int height){
	//a funcao é basicamente a mesma pra todos, sempre fazendo pra um canal de cor cada
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
