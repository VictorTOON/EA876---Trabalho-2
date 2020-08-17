# EA876 - Trabalho 2 

* Álvaro Marques Macêdo - RA 212466
* Victor Toon de Araújo - RA 225231 

## Lógica Utilizada
Primeiramente, a ideia que tivemos foi de utilizar os processos/threads pra resolver cada um dos canais de cor separadamente, assim não temos problemas de conflito entre atividades paralelas. Nós interpretamos o vetor de cada canal como uma matriz de tamanho `[Altura da Imagem em Pixels]x[Largura da Imagem em Pixels]`. Mais sobre a implementação pode ser vista nos comentários dos arquivos principais: `linear.c`, `process.c` e `thread.c`, localizados no diretório `src`.

## Testes 

### Setup Utilizado
Todos os testes foram conduzidos usando o seguinte setup:

![Setup Utilizado](https://github.com/VictorTOON/EA876---Trabalho-2/raw/master/doc/imgs/processador-bolets.png)

Embora estejamos usando o OSX, comparamos os resultados que obtivemos com testes mais rápidos feitos em outras máquinas com Linux e não vimos uma diferença entre o resultados delas e os que iremos apresentar.

### Testes Iniciais 

Como pedido, em cada teste executamos cada variação 100 vezes, decidimos considerar no nosso teste incial o N = 5 e a imagem sendo a encontrada em `./data/cachorro.jpg (1920x1080)`:

![Cachorro.jpg N=5](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-1.png)
![Cachorro.jpg N=5](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-2.png)


O resultado encontrado não foi exatamente o esperado, visto que já que tanto a variação de multiprocessamento quando a de multithread fazem os três canais paralelamente, mas a variação que utiliza o multiprocessamento foi consideravelmente mais lenta que a de multithread. Alternamos então o N para ver se era um caso isolado:

#### N = 3:
![Cachorro.jpg N=3](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-1.png)
![Cachorro.jpg N=3](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-2.png)

#### N = 7:
![Cachorro.jpg N=7](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-1.png)
![Cachorro.jpg N=7](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-2.png)

Mas os resultados também foram semelhantes. Utilizamos também imagens de resoluções diferentes: 

#### `'./data/soundfood.jpeg' (300x300)`:
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/soundfood-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/soundfood-5-3-2.png)

#### `'./data/onePiece.png' (3840x2160)`:
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-2.png)

Vimos então que provavelmente não era uma questão de quais são as entradas (tanto de imagem quando tamanho do N), a proporção entre o tempo do processamento da variação de multiprocessos com a da variação de multithreads permanece relativamente alta.  Com isso em mente, resolvemos ir atrás dos possíveis motivos disso estar acontecendo, entre as hipóteses sobre o porquê disso estar acontecendo, uma delas era que sabendo que o tempo de troca de contexto (_context switching_) do multiprocessos é mais lento que o de threads essa diferença poderia estar causando a diferença no tempo total do processamento, para averiguá-la, testamos o processamento utilizando apenas um canal e depois usando dois canais (scripts para os testes de um canal: `src/linear-1p.c`, `src/process-1p.c`, `src/thread-1p.c` ; scripts para os testes de dois canais: `src/linear-2p.c`, `src/process-2p.c`, `src/thread-2p.c`). Para os dois testes usamos `N = 5` e a imagem como `./data/cachorro.jpg`:

#### Um canal de Cor: 
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-2.png)

#### Dois canais de Cor:
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-2.png)

#### Fazendo a comparação entre o tempo médio do processamento de 1, 2 e 3 canais e considerando mostrando os erros em linhas verticais (considerando `erro =  √(desvio padrão do tempo)`) temos:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/process.png)

Como pudemos observar, o tempo de execução não está mudando de forma significativa se mudarmos o números de processos/threads feitos ao mesmo tempo. Com isso em mente, vemos que o _context switch_ não é o maior influenciador dessa alta diferença de tempo. Uma das susposicões que tivemos após pesquisas que fizemos sobre o desempenho dos processos relacionado ao desempenho das threads é que da forma que o código foi estruturado o tempo de criação e finalização dos processos está significativamente maior do que o das threads. 

## Instruções para a execução dos testes descritos



