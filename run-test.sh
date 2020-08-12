for i in {1..20}; 
	do (./main-l ; ./main-t ; ./main-p) | grep taken ; 
done;

