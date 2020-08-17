# EA876 - Trabalho 2 

* Álvaro Marques Macêdo - RA 212466
* Victor Toon de Araújo - RA 225231 

## Lógica Utilizada
Primeiramente, a ideia que tivemos foi de utilizar os processos/threads pra resolver cada um dos canais de cor separadamente, assim não temos problemas de conflito entre atividades paralelas. Nós interpretamos o vetor de cada canal como uma matriz de tamanho `[Altura da Imagem em Pixels]x[Largura da Imagem em Pixels]`. Mais sobre a implementação pode ser vista nos comentários dos arquivos principais: `linear.c`, `process.c` e `thread.c`, localizados no diretório `src`.

## Testes 

### Setup Utilizado
Todos os testes foram conduzidos usando o seguinte setup:

![alt text](https://github.com/VictorTOON/EA876---Trabalho-2/raw/master/doc/imgs/processador-bolets.png)

Embora estejamos usando o OSX, comparamos os resultados que obtivemos com testes mais rápidos feitos em outras máquinas com Linux e não vimos uma diferença entre o resultados delas e os que iremos apresentar.

### Testes Iniciais 

Como pedido, em cada teste executamos cada variação 100 vezes, decidimos considerar no nosso teste incial o N = 5 e a imagem sendo a encontrada em ./data/cachorro.jpg:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-2.png)


O resultado encontrado não foi exatamente o esperado, visto que já que tanto a variação de multiprocessamento quando a de multithread fazem os três canais paralelamente, mas a variação que utiliza o multiprocessamento foi consideravelmente mais lenta que a de multithread. Alternamos então o N para ver se era um caso isolado:

#### N = 3
![Cachorro.jpg N=3](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-1.png)
![Cachorro.jpg N=3](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-2.png)

#### N = 5
![Cachorro.jpg N=7](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-1.png)
![Cachorro.jpg N=7](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-2.png)

Mas os resultados também foram semelhantes. Por fim, resolvemos testar com uma imagem muito grande (resolução 4k), e obtivemos o seguinte resultado:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-2.png)

Com isso em mente, resolvemos ir atrás dos possíveis motivos disso estar acontecendo, já que tanto o multi-thread quanto o multi-processos são feitas em paralelo. Então fizemos alguns testes com apenas 1 canal de cor e com 2 canais, pra saber se haveria diferença na velocidade(não deveria haver, teoricamente). Obtivemos os seguintes resultados:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-2.png)

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-2.png)

Como pudemos observar, o tempo de execução se mantém se mudarmos o números de processos/threads feitos ao mesmo tempo. Com isso em mente, e fazendo algumas pesquisas, supomos que o que fez nosso multi-processo demorar tanto a mais é que os processos normalmente demoram mais para serem criados e para finalizarem. Além de que o tempo de "context switch" do Processo ser maior do que da Thread. Nos processos também, utilizamos mmap pra declarar as matrizes utilizadas dentro deles, e o mmap demora mais tempo para ser criado do que um malloc normal.

## Instruções para a execução dos testes descritos
