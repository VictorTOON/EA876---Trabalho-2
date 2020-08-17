LINEAR_FLAGS=-lfreeimage -Wextra
THREAD_FLAGS=-lfreeimage -lpthread -Wextra
PROCESS_FLAGS=-lfreeimage -Wextra
N=5
IMAGE=./data/cachorro.jpg
N_ITERATIONS=100

all: build/linear.o build/thread.o build/process.o

build/linear.o: src/linear.c
	gcc -o build/linear.o src/linear.c src/imageprocessing.c -I./ $(LINEAR_FLAGS)
build/thread.o: src/thread.c
	gcc -o build/thread.o src/thread.c src/imageprocessing.c -I./ $(THREAD_FLAGS)
build/process.o: src/thread.c
	gcc -o build/process.o src/process.c src/imageprocessing.c -I./ $(PROCESS_FLAGS)

all-2p: build/linear-2p.o build/thread-2p.o build/process-2p.o

build/linear-2p.o: src/linear-2p.c
	gcc -o build/linear-2p.o src/linear-2p.c src/imageprocessing.c -I./ $(LINEAR_FLAGS)
build/thread-2p.o: src/thread-2p.c
	gcc -o build/thread-2p.o src/thread-2p.c src/imageprocessing.c -I./ $(THREAD_FLAGS)
build/process-2p.o: src/thread-2p.c
	gcc -o build/process-2p.o src/process-2p.c src/imageprocessing.c -I./ $(PROCESS_FLAGS)

all-1p: build/linear-1p.o build/thread-1p.o build/process-1p.o

build/linear-1p.o: src/linear-1p.c
	gcc -o build/linear-1p.o src/linear-1p.c src/imageprocessing.c -I./ $(LINEAR_FLAGS)
build/thread-1p.o: src/thread-1p.c
	gcc -o build/thread-1p.o src/thread-1p.c src/imageprocessing.c -I./ $(THREAD_FLAGS)
build/process-1p.o: src/thread-1p.c
	gcc -o build/process-1p.o src/process-1p.c src/imageprocessing.c -I./ $(PROCESS_FLAGS)

install:
	mkdir build

clean:
	rm build/*
test:
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE)
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE)
endif
test-1p:
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -1p
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -1p
endif
test-2p:
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -2p
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -2p
endif
