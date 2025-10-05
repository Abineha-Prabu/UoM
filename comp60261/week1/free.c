#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_array(int size){
	int *arr = (int *) malloc (size *sizeof(int));
	if (arr == NULL){
		printf("error: cant allocate memory. \n");
		exit(-1);
	}
	for(int i=0;i<size;i++){
		arr[i] = i*i;
		printf("%d \n", arr[i]);
	}
	free(arr);
}

int main(){
	int n;
	printf("enter the size of array \n");
	scanf("%d", &n);
	if (n>0){
		process_array(n);
	}
	printf("all good \n");
	return 0;
}
