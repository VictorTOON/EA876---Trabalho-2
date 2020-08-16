#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "imageprocessing.h"

int main(int argc, char *argv[]){
    imagem img, novaImg;
    //le o valor de N do makefile
    int N = atoi(argv[1]);

    img = abrir_imagem(argv[2]);
    novaImg = abrir_imagem(argv[2]);

    float somaR = 0, somaG = 0, somaB = 0, quant = 0;
    //variáveis pra medir o tempo
    struct timeval start, stop;
    double secs = 0;

    //Daqui em diante é a forma linear de fazer, sem processamento paralelo
    //A ideia é a seguinte, temos 4 fors encadiados
    //os dois primeiros vão passar pelas matrizes de pixels
    //os dois seguintes vao olhar ao redor de cada pixel
    //e dentro de tudo a gente soma pra fazer a média dos pixels
    //o que fazemos é resolver cada canal de cor, um de cada vez


    //Canal vermelho
    gettimeofday(&start, NULL);
    for (int i = 0; i < (img.width); i++){
        for (int j = 0; j < (img.height); j++){
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
            novaImg.r[j * img.width + i] = somaR / quant;

            somaR = 0;
            quant = 0;
        }
    }
    //canal verde
    for (int i = 0; i < (img.width); i++){
        for (int j = 0; j < (img.height); j++){
            for (int l = j - N; l < j + N; l++){
                if (l >= 0 && l < img.height){
                    for (int k = i - N; k < i + N; k++){
                        if (k >= 0 && k < img.width){
                            somaG = somaG + img.g[l * img.width + k];
                            quant++;
                        }
                    }
                }
            }
            novaImg.g[j * img.width + i] = somaG / quant;

            somaR = 0;
            somaG = 0;
            somaB = 0;
            quant = 0;
        }
    }
    //canal azul
    for (int i = 0; i < (img.width); i++){
        for (int j = 0; j < (img.height); j++){
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
            novaImg.b[j * img.width + i] = somaB / quant;

            somaR = 0;
            somaG = 0;
            somaB = 0;
            quant = 0;
        }
    }

    //função pra medir o tempo gasto
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken linear: %f\n", secs);

    if (argc > 3){
        salvar_imagem(argv[3], &novaImg);
    }
    else{
        salvar_imagem("ouput-linear.jpg", &novaImg);
    }
    liberar_imagem(&novaImg);
    liberar_imagem(&img);
    return 0;
}
