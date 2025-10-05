#include <stdio.h>
#include <string.h>

int main(){
	int int1,int2;
	double double1;
	float float1;
	char s[128];
	
	printf("please ip a string: \n");
	fgets(s, 128, stdin);
	printf("please ip an int: \n");
	scanf("%d", &int1);
	printf("please ip a double: \n");
	scanf("%lf", &double1);
	printf("please ip an int and float sep by space");
	scanf("%d %f", &int2, &float1);
	printf("you entered: %d, %d, %lf, %f, %s \n", int1, int2, double1, float1, s);
}
