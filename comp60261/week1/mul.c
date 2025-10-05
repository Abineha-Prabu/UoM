#include <stdio.h>
#include <string.h>

int multiply_and_divide(int n1, int n2, int *product, int *quotient){
	if (n2==0) return -1;
	*product = n1*n2;
	*quotient = n1/n2;
	return 0;
}

int main(int argv, char **argc){
	int p,q,a = 5, b = 10;
	if (multiply_and_divide(a,b,&p, &q)==0){
		printf("10*5 = %d \n", p);
		printf("10/5 = %d \n", q);
	}
}
