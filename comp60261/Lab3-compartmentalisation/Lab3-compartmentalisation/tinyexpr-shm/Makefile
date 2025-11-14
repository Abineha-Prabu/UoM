CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -pthread -lrt -lm

BINS = example example2 test-suite benchmark shm-lib

all: shm-lib $(BINS)

example: example.c tinyexpr.c shm-main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

example2: example2.c tinyexpr.c shm-main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test-suite: test-suite.c tinyexpr.c shm-main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

benchmark: benchmark.c tinyexpr.c shm-main.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

shm-lib: shm-lib.c tinyexpr.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(BINS) *.o

zip:
	rm -rf comp-shm
	mkdir comp-shm
	cp *.c *.h Makefile comp-shm
	zip -r comp-shm.zip comp-shm/
	rm -rf comp-shm

