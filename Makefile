LINEAR_FLAGS=-lfreeimage -Wextra
THREAD_FLAGS=-lfreeimage -lpthread -Wextra
PROCESS_FLAGS=-lfreeimage -Wextra
all: build/linear.o build/thread.o build/process.o

build/linear.o: src/linear.c
	gcc -o build/linear.o src/linear.c src/imageprocessing.c -I./ $(LINEAR_FLAGS)
build/thread.o: src/thread.c
	gcc -o build/thread.o src/thread.c src/imageprocessing.c -I./ $(THREAD_FLAGS)
build/process.o: src/thread.c
	gcc -o build/process.o src/process.c src/imageprocessing.c -I./ $(PROCESS_FLAGS)

install:
	mkdir build

clean:
	rm build/*
test:
	sh run-test.sh 
