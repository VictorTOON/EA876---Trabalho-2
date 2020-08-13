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
#define N 5

int main(){
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Criar area de memoria compartilhada */
    imagem img;
    img = abrir_imagem("./data/cachorro.jpg");
    float *matriz1 = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);
    float *matriz2 = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);
    float *matriz3 = (float *)mmap(NULL, sizeof(float) * img.height * img.width, protection, visibility, 0, 0);

    unsigned int somaR = 0, somaG = 0, somaB = 0, quant = 0;

    float alpha = 0.998;
    struct timeval start, stop;
    double secs = 0;

    //Daqui em diante é a forma multithread
    gettimeofday(&start, NULL);
    pid_t p1, p2, p3;
    p1 = fork();
    if (p1 == 0){
        for (int i = 0; i < (img.width); i++){
            for (int j = 0; j < (img.height); j++){
                //Blur normal no canal R
                for (int l = j - N; l < j + N; l++){
                    if (l >= 0 && l < img.height){
                        for (int k = i - N; k < i + N; k++){
                            if (k >= 0 && k < img.width){
                                somaR = somaR + img.r[l * img.width + k];
                                quant++;
                            }
                        }
                    }
                }
                matriz1[j * img.width + i] = somaR / quant;
                somaR = 0;
                quant = 0;
            }
        }
        exit(0);
    }
    p2 = fork();
    if (p2 == 0){
        //printf("Entrei processo 2\n");
        for (int i = 0; i < (img.width); i++){
            for (int j = 0; j < (img.height); j++){
                //Blur normal no canal G
                for (int l = j - N; l < j + N; l++){
                    if (l >= 0 && l < img.height){
                        for (int k = i - N; k < i + N; k++){
                            if (k >= 0 && k < img.width){
                                somaG = somaG+ img.g[l * img.width + k];
                                quant++;
                            }
                        }
                    }
                }
                matriz2[j * img.width + i] = somaG / quant;
                somaG = 0;
                quant = 0;
            }
        }
        //printf("sai processo 2\n");
        exit(0);
    }
    p3 = fork();
    if (p3 == 0){
        //printf("Entrei processo 3\n");
        for (int i = 0; i < (img.width); i++){
            for (int j = 0; j < (img.height); j++){
                //Blur normal no canal B
                for (int l = j - N; l < j + N; l++){
                    if (l >= 0 && l < img.height){
                        for (int k = i - N; k < i + N; k++){
                            if (k >= 0 && k < img.width){
                                somaB = somaB + img.b[l * img.width + k];
                                quant++;
                            }
                        }
                    }
                }
                matriz3[j * img.width + i] = somaB / quant;
                somaB = 0;
                quant = 0;
            }
        }
        //printf("sai processo 3\n");
        exit(0);
    }

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    memcpy(img.r, matriz1, sizeof(float) * img.height * img.width);
    memcpy(img.g, matriz2, sizeof(float) * img.height * img.width);
    memcpy(img.b, matriz3, sizeof(float) * img.height * img.width);

    gettimeofday(&stop, NULL);

    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken multi process: %f\n", secs);

    salvar_imagem("cachorro-out-multi-process.jpg", &img);
    liberar_imagem(&img);
    return 0;
}