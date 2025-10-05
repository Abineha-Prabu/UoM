#include <stdio.h>
#include <string.h>

typedef struct{
	int x;
	float f;
	char *s;
} my_struct;

int main(){
	my_struct ms = {42, 2.5, "hello"};
	my_struct *ptr = &ms;

	printf("%d \n", (*ptr).x);
	printf("%s \n", ptr -> s);
}
