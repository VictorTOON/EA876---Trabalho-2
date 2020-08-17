LINEAR_FLAGS=-lfreeimage -Wextra
THREAD_FLAGS=-lfreeimage -lpthread -Wextra
PROCESS_FLAGS=-lfreeimage -Wextra
N=5
IMAGE=./data/soundfood.png
N_ITERATIONS=100
UNAME_S := $(shell uname -s)

all: install build/linear.o build/thread.o build/process.o all-1p all-2p

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
	if [ -d "build" ]; then echo "saving in build.."; else mkdir build; fi;
clean:
	rm build/*
test:
	chmod +x run-test.sh
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) | python3 plot-graph.py
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) | python3 plot-graph.py
endif
test-1p:
	chmod +x run-test.sh
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -1p | python3 plot-graph.py
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -1p | python3 plot-graph.py
endif
test-2p:
	chmod +x run-test.sh
ifeq ($(UNAME_S),Linux)
	./run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -2p | python3 plot-graph.py
endif
ifeq ($(UNAME_S),Darwin)
	sh run-test.sh $(N_ITERATIONS) $(N) $(IMAGE) -2p | python3 plot-graph.py
endif
