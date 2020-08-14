#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "imageprocessing.h"
#define N 5

int main() {
  imagem img, novaImg;
  img = abrir_imagem("./data/onepiece.jpg");
  novaImg = abrir_imagem("./data/onepiece.jpg");

  float somaR = 0, somaG = 0, somaB = 0, quant = 0;

  float alpha = 0.998;
  struct timeval start, stop;
  double secs = 0;

  //Daqui em diante é a forma linear de fazer, sem processamento paralelo
  gettimeofday(&start, NULL);
  for (int i=0; i<(img.width); i++) {
    for (int j=0; j<(img.height); j++) {
        //Blur normal no canal R
        for(int l = j - N; l < j + N; l++){
            if(l>=0 && l < img.height){
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
  for (int i=0; i<(img.width); i++) {
    for (int j=0; j<(img.height); j++) {
        //Blur normal no canal R
        for(int l = j - N; l < j + N; l++){
            if(l>=0 && l < img.height){
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
  for (int i=0; i<(img.width); i++) {
    for (int j=0; j<(img.height); j++) {
        //Blur normal no canal R
        for(int l = j - N; l < j + N; l++){
            if(l>=0 && l < img.height){
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
  gettimeofday(&stop, NULL);
  secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  printf("time taken linear: %f\n", secs);

  salvar_imagem("cachorro-out-linear.jpg", &novaImg);
  liberar_imagem(&novaImg);
  return 0;
}
