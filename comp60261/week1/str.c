#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	char *string1 = "hello";
	char *string2 = string1;
	char string3[10];

	strcpy(string3, string1);
	strncpy(string3, string1, 10);

	printf("string1 @%p: %s \n", string1,string1);
	printf("string2 @%p: %s \n", string2, string2);
	printf("string3 @%p: %s \n", string3, string3);
}
