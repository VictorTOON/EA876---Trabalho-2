
for i in {1..100}; 
	do (./build/linear$1.o 5 ./data/cachorro.jpg ; ./build/thread$1.o 5 ./data/cachorro.jpg; ./build/process$1.o 5 ./data/cachorro.jpg) | grep taken ; 
done;

