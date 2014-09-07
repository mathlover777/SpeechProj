#include <stdio.h>
#include <stdlib.h>
#include "fileio.c"
const char *metafile="metafile.txt";
int main(int argc,char **argv){
	// input.txt -- argv[1] outputWav.txt-->argv[2]
	resetfile(argv[2]);
	int mflag,eflag;
	FILE *fm=initializeFileRead(metafile,&mflag);
	FILE *f=initializeFileRead(argv[1],&eflag);
	char buffer[1000];
	/************* writting meta data ***********/
	readLine(fm,buffer,&mflag);
	addLine(argv[2],buffer);
	readLine(fm,buffer,&mflag);
	addLine(argv[2],buffer);
	readLine(fm,buffer,&mflag);
	addLine(argv[2],buffer);
	readLine(fm,buffer,&mflag);
	addLine(argv[2],buffer);
	readLine(fm,buffer,&mflag);
	addLine(argv[2],buffer);
	fclose(fm);
	/********************************************/
	int x;
	double y;
	while(1){
		readLine(f,buffer,&eflag);
		sscanf(buffer,"%lf",&y);
		// y=y/4701.0;
		x=(int)y;
		if(buffer[0]=='\0'){
			break;
		}
		sprintf(buffer,"%d",x);
		addLine(argv[2],buffer);
	}
	fclose(f);
	return 0;
}