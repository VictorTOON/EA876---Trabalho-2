
for i in {1..100}; 
	do (./build/linear$3.o $1 $2 ; ./build/thread$3.o $1 $2; ./build/process$3.o $1 $2) | grep taken ; 
done;

