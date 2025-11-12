BINS=example-monolithic example-comp-pipe-main example-comp-pipe-lib \
	example-comp-shm-main example-comp-shm-lib

all: $(BINS)

example-monolithic: example-monolithic.c
	gcc $^ -o $@

example-comp-pipe-main: example-comp-pipe-main.c example-comp-pipe.h
	gcc example-comp-pipe-main.c -o $@

example-comp-pipe-lib: example-comp-pipe-lib.c example-comp-pipe.h
	gcc example-comp-pipe-lib.c -o $@

example-comp-shm-main: example-comp-shm-main.c example-comp-shm.h
	gcc example-comp-pipe-main.c -o $@

example-comp-shm-lib: example-comp-shm-lib.c example-comp-shm.h
	gcc example-comp-shm-lib.c -o $@

zip:
	rm -rf comp-example
	mkdir comp-example
	cp *.c *.h Makefile comp-example
	zip -r comp-example.zip comp-example/
	rm -rf comp-example

clean:
	rm -rf *.o $(BINS)