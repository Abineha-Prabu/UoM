#include <stdio.h>
#include <string.h>

int swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(){
	int x = 10;
	int y = 100;
	swap(&x, &y);
	printf("x = %d, y = %d \n", x, y);
}

