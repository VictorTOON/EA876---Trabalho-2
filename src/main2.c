#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "imageprocessing.h"
#define N 7

void *funcao_thread1(void *count);
imagem img;

int main(){
    img = abrir_imagem("./data/cachorro.jpg");
    unsigned int somaR = 0, somaG = 0, somaB = 0, quant = 0;

    float alpha = 0.998;
    struct timeval start, stop;
    double secs = 0;

    //Daqui em diante é a forma multithread
    gettimeofday(&start, NULL);
    pthread_t p1, p2, p3;

    void *arg1 = malloc(sizeof(float *));
    void *arg2 = malloc(sizeof(float *));
    void *arg3 = malloc(sizeof(float *));
    (arg1) = img.r;
    (arg2) = img.g;
    (arg3) = img.b;

    pthread_create(&(p1), NULL, funcao_thread1, arg1);
    pthread_create(&(p2), NULL, funcao_thread1, arg2);
    pthread_create(&(p3), NULL, funcao_thread1, arg3);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken multi thread: %f\n", secs);

    salvar_imagem("cachorro-out-multi-thread.jpg", &img);
    liberar_imagem(&img);
    return 0;
}

void *funcao_thread1(void *arg){
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