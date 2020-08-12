
main: src/main2.c src/main.c src/main3.c
	gcc -omain src/main.c src/imageprocessing.c -I./ -lfreeimage
	./main
	gcc -omain src/main2.c src/imageprocessing.c -I./ -lfreeimage
	./main
	gcc -omain src/main3.c src/imageprocessing.c -I./ -lfreeimage
	./main