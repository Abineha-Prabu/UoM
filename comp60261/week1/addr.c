#include <stdio.h>
#include <string.h>

int main(){
	int x = 27;
	printf("0x %x \n", &x);

	int *ptr = &x;
	printf("%d \n", *ptr);
}
