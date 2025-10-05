#include <stdio.h>

int main(){
	int i, choice =1;
	for (i=0; i<5;i++){
		printf("for loop iteration %d \n", i);
	}
	
	i = 0;	
	while(i<5){
		printf("while loop iteration %d \n", i);
		i ++;
	}

	switch(choice){
		case 1:
			printf("choice is 1\n");
			break;
		case 2:
			printf("choice is 2\n");
			break;
		default:
			printf("choice is neither 1 nor 2\n");
	}
}
