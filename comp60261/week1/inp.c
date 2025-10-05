#include <stdio.h>
#include <string.h>

void process_array(int size){
	int arr[size];
	for(int i=0;i<size;i++){
		arr[i] = i*i;
		printf("%d \n", arr[i]);
	}
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
