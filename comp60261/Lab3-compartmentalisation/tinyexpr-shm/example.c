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
