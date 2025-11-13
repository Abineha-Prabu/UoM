#include "custom_tinyexpr.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int err;

    if (argc < 2) {
        printf("Usage: example2 \"expression\"\n");
        return 0;
    }
    const char *expression = argv[1];
    printf("Evaluating:\n\t%s\n", expression);

    double res = te_interp(expression, &err);
    printf("result: %lf\n", res);

    return 0;
}
