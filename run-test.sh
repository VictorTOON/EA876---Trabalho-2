for i in {1..20}; 
	do (./build/linear.o ; ./build/thread.o ; ./build/process.o) | grep taken ; 
done;

