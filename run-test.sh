for i in {1..20}; 
	do (./build/linear.o 5 ./data/cachorro.jpg ; ./build/thread.o 5 ./data/cachorro.jpg; ./build/process.o 5 ./data/cachorro.jpg) | grep taken ; 
done;

