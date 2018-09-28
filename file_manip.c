#include <stdio.h>
#include <stdlib.h>
#include "myio.h"


int main(int argc, char* argv[]){
	MYFILE *fp;
	char buff[100];

	fp = myopen("Makefile", "r");
	fp = myopen("Swag", "r");

	myread(buff, 10, 1, fp);

	printf("%s\n", buff);

	perror("error");



}
