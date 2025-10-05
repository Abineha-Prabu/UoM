#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int m1; int m2; int m3; float f1;
} my_struct;

int main(){
	int arr_size = 10;
	my_struct arr1[arr_size];
	my_struct arr2[arr_size];
	
	for(int i=0;i<arr_size;i++){
		arr1[i].m1 = 1;
		arr1[i].m2 = 2;
		arr1[i].m3 = 3;
		arr1[i].f1 = 4.0;
	}

	memcpy(arr2, arr1, arr_size *sizeof(my_struct));
}
