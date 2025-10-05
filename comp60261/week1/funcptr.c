#include <stdio.h>
#include <string.h>

void greet_v1(char *name){
	printf("good morning, %s! \n", name);
}

void greet_v2(char *name){
	printf("good evening, %s! \n", name);
}

int main(){
	void (*func_ptr)(char *);
	char *username = "Pierre";
	func_ptr = greet_v1;
	func_ptr(username);
	func_ptr = greet_v2;
	func_ptr(username);
	return 0;
}
