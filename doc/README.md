Primeiramente, a ideia que tivemos foi de utilizar os processos/threads pra resolver cada um dos canais de cor separadamente. Sendo assim, no arquivo de multi-thread e de multi-processos, temos 3 thread e 3 processos.

Primeiramente, todos os nossos gráficos e testes foram feitos com o seguinte setup:

![alt text](https://github.com/VictorTOON/EA876---Trabalho-2/raw/master/doc/imgs/processador-bolets.png)

Nisso, nós obtivemos os seguintes testes para N = 5:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-3-2.png)

Com isso, podemos ver que o resultado não foi exatamente como o esperado, já que o multi-processos está consideravelmente distante da multi-thread. Então, testamos para N = 3 e N = 7:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-3-3-2.png)

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-7-3-2.png)

Mas os resultados também foram semelhantes. Por fim, resolvemos testar com uma imagem muito grande (resolução 4k), e obtivemos o seguinte resultado:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/onePiece-5-3-2.png)

Com isso em mente, resolvemos ir atrás dos possíveis motivos disso estar acontecendo, já que tanto o multi-thread quanto o multi-processos são feitas em paralelo. Então fizemos alguns testes com apenas 1 canal de cor e com 2 canais, pra saber se haveria diferença na velocidade(não deveria haver, teoricamente). Obtivemos os seguintes resultados:

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-1-2.png)

![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-1.png)
![alt text](https://raw.githubusercontent.com/VictorTOON/EA876---Trabalho-2/master/doc/imgs/cachorro-5-2-2.png)

Como pudemos observar, o tempo de execução se mantém se mudarmos o números de processos/threads feitos ao mesmo tempo. Com isso em mente, e fazendo algumas pesquisas, supomos que o que fez nosso multi-processo demorar tanto a mais é que os processos normalmente demoram mais para serem criados e para finalizarem. Além de que o tempo de "context switch" do Processo ser maior do que da Thread. Nos processos também, utilizamos mmap pra declarar as matrizes utilizadas dentro deles, e o mmap demora mais tempo para ser criado do que um malloc normal.
