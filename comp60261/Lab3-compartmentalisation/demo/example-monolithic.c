#include <stdio.h>

int global;

int library_function(int *parameter) {
    char *cryptokey = "private";
    int ret = *parameter + global + 42;
    return ret;
}

int main() {
    int arg = 100;
    global = 50;
    char *password = "secret";
    
    int res = library_function(&arg);
    
    printf("res: %d\n", res);

    return 0;
}