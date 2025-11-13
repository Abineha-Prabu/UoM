CC = gcc
CCFLAGS = -g -Wall
LFLAGS = -lm

.PHONY = all clean

all: example example2 test-suite benchmark

test-suite: test-suite.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

benchmark: benchmark.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example: example.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example2: example2.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o *.exe example example2 benchmark test-suite
