for i in {1..20}; 
	do (./build/linear.o 5 ./data/onepiece.jpg ; ./build/thread.o 5 ./data/onepiece.jpg; ./build/process.o 5 ./data/onepiece.jpg) | grep taken ;
done;
