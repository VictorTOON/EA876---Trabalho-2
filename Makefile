
main: src/main2.c src/main.c src/main3.c
	gcc -omain-l src/main.c src/imageprocessing.c -I./ -lfreeimage
	gcc -omain-t src/main2.c src/imageprocessing.c -I./ -lfreeimage -lpthread
	gcc -omain-p src/main3.c src/imageprocessing.c -I./ -lfreeimage
clean:
	rm main*
test:
	sh run-test.sh 
