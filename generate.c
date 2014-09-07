#include <stdio.h>
#include <stdlib.h>

const char *filename="input.txt";
int main(int argc,char **argv){
	FILE *f=fopen(filename,"w");
	double x;
	for(int i=0;i<atoi(argv[1]);i++){
		x=rand()%100;
		fprintf(f,"%lf\n",x);
	}
	fclose(f);
	return 0;
}