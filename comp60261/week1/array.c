#include <stdio.h>

int main(){
	int array[4];
	array[0] = 42;
	array[1] = 43;
	array[2] = 44;
	array[3] = 45;
	printf("%d\n", array[2]);

	int array2[2][2];
	array2[0][0] = 12;
	array2[0][1] = 13;
	array2[1][0] = 14;
	array2[1][1] = 15;

	char str[3];
	str[0] = 'h';
	str[1] = 'i';
	str[2] = '\0';
	printf("%s\n", str);
}
