# Tinyexpr

This is a simplified version of tinyexpr, which original source code can be found here: https://github.com/codeplea/tinyexpr.

TinyExpr is a very small recursive descent parser and evaluation engine for math expressions. It's handy when you want to add the ability to evaluate math expressions at runtime without adding a bunch of cruft to your project.

## Using the Library

Simply include `tinyexpr.h` in your C file and use `te_interp` to evaluate math expressions.
For example this is `example.c`:

```c
#include "tinyexpr.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *c = "sqrt(5^2+7^2+11^2+(8-2)^2)";
    int err;

    double r = te_interp(c, &err);

    if(err) {
        printf("ERROR evaluating %s\n", c);
        return -1;
    }

    printf("The expression %s evaluates to: %f\n", c, r);
    return 0;
}
```

Build and it as follows:

```bash
gcc example.c tinyexpr.c -o example -lm
./example
The expression sqrt(5^2+7^2+11^2+(8-2)^2) evaluates to: 15.198684
```

## Test suite

Test as follows:

```
gcc test-suite.c tinyexpr.c -o test-suite -lm
./test-suite
# ...
ALL TESTS PASSED (198/198)
```

## Benchmark

To measure the speed of the library and compare it to native execution of math computation directly in C code:

```
gcc benchmark.c tinyexpr.c -o benchmark -lm
./benchmark
Expression: sqrt(5^2+7^2+11^2+(8-2)^2)
Evaluated result: 15.1986841536
Native result: 15.1986841536
Total time: 0.073291 seconds
Evaluations per second: 1364429
Native total time: 0.000093 seconds
Native evaluations per second: 1079552202
```
