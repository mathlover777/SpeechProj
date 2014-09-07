#include <stdio.h>
#include <stdlib.h>
#include "fileio.c"
const char *metafile="metafile.txt";

int main(int argc,char **argv){
	int endflag;
	printf("\nARGV[1] = {%s}",argv[1]);
	FILE *f=initializeFileRead(argv[1],&endflag);
	// printf("\nf = %p",f);
	resetfile(metafile);
	char buffer[1000];
	readLine(f,buffer,&endflag);
	printf("{%s}\n",buffer);
	addLine(metafile,buffer);
	readLine(f,buffer,&endflag);
	printf("{%s}\n",buffer);
	addLine(metafile,buffer);
	readLine(f,buffer,&endflag);
	printf("{%s}\n",buffer);
	addLine(metafile,buffer);
	readLine(f,buffer,&endflag);
	printf("{%s}\n",buffer);
	addLine(metafile,buffer);
	readLine(f,buffer,&endflag);
	printf("{%s}\n",buffer);
	addLine(metafile,buffer);
	resetfile(argv[2]);
	while(1){
		readLine(f,buffer,&endflag);
		if(buffer[0]=='\0'){
			break;
		}
		addLine(argv[2],buffer);
	}
	fclose(f);
	return 0;
}