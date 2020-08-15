#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "imageprocessing.h"

int main(int argc, char *argv[]) {
  imagem img, novaImg;
  int N = atoi(argv[1]);
  img = abrir_imagem(argv[2]);
  novaImg = abrir_imagem(argv[2]);

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
  gettimeofday(&stop, NULL);
  secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  printf("time taken linear: %f\n", secs);

  if (argc > 3){
  	salvar_imagem(argv[3], &novaImg);
  } else {
  	salvar_imagem("./output.jpg", &novaImg);
  }
  liberar_imagem(&novaImg);
  liberar_imagem(&img);
  return 0;
}
