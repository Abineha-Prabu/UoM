CC = gcc
CCFLAGS = -g -Wall
LFLAGS = -lm

.PHONY = all clean

BINS = example example2 test-suite benchmark te_sandbox

all: $(BINS)

te_sandbox: te_sandbox.c tinyexpr.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

test-suite: test-suite.c te_client.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

benchmark: benchmark.c te_client.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example: example.c te_client.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example2: example2.c te_client.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o *.exe $(BINS)
	rm -f /tmp/te_param.pipe /tmp/te_result.pipe
