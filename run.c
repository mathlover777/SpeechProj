#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	system("reset");
	// argv[1] = ascii wav file
	// argv[2] = output wav file 1
	// argv[3] = output wav file 2
	// if no argument is given then input is "wavfile.txt" output is "outputwav1.txt"
	// and "outputwav2.txt"
	char wavinput[100],outputwav1[100],outputwav2[100],outputwav3[100];
	double ALPHA;
	int OVERLAP,FRAMESIZE,LPCORDER,F0;

	if(argc!=10){
		sprintf(wavinput,"wavfile.txt");
		sprintf(outputwav1,"outputwav1.txt");
		sprintf(outputwav2,"outputwav2.txt");
		sprintf(outputwav3,"outputwav3.txt");
		ALPHA=0.95;
		OVERLAP=5;
		FRAMESIZE=50;
		LPCORDER=16;
		F0=6;
	}else{
		sprintf(wavinput,"%s",argv[1]);
		sprintf(outputwav1,"%s",argv[2]);
		sprintf(outputwav2,"%s",argv[3]);
		sprintf(outputwav3,"%s",argv[4]);
		sscanf(argv[5],"%lf",&ALPHA);
		sscanf(argv[6],"%d",&OVERLAP);
		sscanf(argv[7],"%d",&FRAMESIZE);
		sscanf(argv[8],"%d",&LPCORDER);
		sscanf(argv[9],"%d",&F0);
	}
	char call[1000];
	sprintf(call,"./wavToInput %s input.txt",wavinput);
	system(call);
	sprintf(call,"./driver %lf %d %d %d %d",ALPHA,OVERLAP,FRAMESIZE,LPCORDER,F0);
	system(call);
	sprintf(call,"./InputToWav outputFromError.txt %s",outputwav1);
	system(call);
	sprintf(call,"./InputToWav outputFromImpulse.txt %s",outputwav2);
	system(call);
	sprintf(call,"./InputToWav impulsegen.txt %s",outputwav3);
	system(call);

	return 0;
}