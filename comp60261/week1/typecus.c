#include <stdio.h>
#include <string.h>

typedef struct s_person{
	char name[10];
	float size_in_meters;
	int weight_in_grams;
};

typedef struct s_person person;

void print_person(person p){
	printf("%s has a size of %f in meters and weighs %d grams\n", p.name, p.size_in_meters, p.weight_in_grams);
}

int main(int argc, char ** argv){
	person p1;
	p1.size_in_meters = 1.6;
	p1.weight_in_grams = 60000;
	strcpy(p1.name, "Julie");
	
	person p2 = {"George", 1.8, 70000};
	print_person(p1);
	print_person(p2);
	return 0;
}

