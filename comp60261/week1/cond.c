#include <stdio.h>

int add(int a, int b){
	return a+b;
}

int main(){
	int result = add(2, 2);
	printf("2+2 = %d \n", result);
}
