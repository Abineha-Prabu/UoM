#include <stdio.h>
#include <string.h>

int main(){
	char world[6] = "world";
	char s1[32];
	char s2[32];
	strcpy(s1, "hello");
	strcpy(s2, "hello");
	strcat(s1, world);
	strncat(s2, world, 32-strlen(s2));
	printf("s1: %s \n", s1);
	printf("s2: %s \n", s2);
}
