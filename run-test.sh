
for i in $(seq 1 $1); 
	do (./build/linear$4.o $2 $3 ; ./build/thread$4.o $2 $3; ./build/process$4.o $2 $3) | grep taken ; 
done;

