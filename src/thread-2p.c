#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "imageprocessing.h"

//mesmo código da thread normal, mas com apenas 2 canais de cor e 2 threads rolando

void *funcao_thread(void *count);
imagem img;
static int N;
int main(int argc, char *argv[]){
    N = atoi(argv[1]);
    img = abrir_imagem(argv[2]);
    unsigned int somaR = 0, somaG = 0, somaB = 0, quant = 0;

    float alpha = 0.998;
    struct timeval start, stop;
    double secs = 0;

    //Daqui em diante é a forma multithread
    gettimeofday(&start, NULL);
    pthread_t p1;
    pthread_t p2;

    void *arg1 = malloc(sizeof(float *));
    void *arg2 = malloc(sizeof(float *));
    (arg1) = img.r;
    (arg2) = img.g;

    pthread_create(&(p1), NULL, funcao_thread, arg1);
    pthread_create(&(p2), NULL, funcao_thread, arg2);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken multi thread: %f\n", secs);

    if (argc > 3){
	salvar_imagem(argv[3], &img);
    } else {
	salvar_imagem("./output-thread.jpg", &img);
    }
    liberar_imagem(&img);
    return 0;
}

void *funcao_thread(void *arg){
    float* matriz = malloc(sizeof(float)*img.height*img.width);
    memcpy(matriz, arg, (sizeof(float) * img.height * img.width));
    float soma = 0, quant = 0;

    for (int i = 0; i < (img.width); i++){
        for (int j = 0; j < (img.height); j++){
            //Blur normal no canal R
            for (int l = j - N; l < j + N; l++){
                if (l >= 0 && l < img.height){
                    for (int k = i - N; k < i + N; k++){
                        if (k >= 0 && k < img.width){
                            soma = soma + matriz[l * img.width + k];
                            quant++;
                        }
                    }
                }
            }
            ((float*)arg)[j * img.width + i] = soma / quant;
            soma = 0;
            quant = 0;
        }
    }
    return NULL;
}
