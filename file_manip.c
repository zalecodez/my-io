#include <stdio.h>
#include "myio.h"
#include <stdlib.h>


int main(int argc, char* argv[]){

	myopen("./Swag", "r");
	myopen("./Swag", "r+");
	myopen("./Swag", "w");
	myopen("./Swag", "w+");
	myopen("./Swag", "a");
	myopen("./Swag", "a+");
	

	printf("%i",fopen("./Makefile", "refd"));

}
