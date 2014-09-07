/*
AUTHOR(S) : SOURAV SARKAR
			SIKHAR PATRANABIS
			SUBHAM DE
DATE : NOV 30,2013
*/
#include <stdio.h>
#include <stdlib.h>
#include "frame.cpp"
#include "LPC.c"
#include "FILTER.c"
#include <math.h>

#define ERROR .0001
// #define ALPHA .95
// #define FSIZE 50
// #define OVERLAP 10
// #define NOOVERLAP 0
// #define LPCORDER 16
// #define MAXSAMPLESIZE 100000
// #define F0 6

#define ALPHA argALPHA
#define FSIZE argFSIZE
#define OVERLAP argOVERLAP
#define NOOVERLAP 0
#define LPCORDER argLPCORDER
#define MAXSAMPLESIZE 100000
#define F0 argF0

double argALPHA;
int argFSIZE,argF0,argLPCORDER,argOVERLAP;

const char *filename="input.txt";
const char *efilename="outputFromError.txt";
const char *ifilename="outputFromImpulse.txt";
const char *impulsefile="impulsegen.txt";

double **FRAMES;
double **GFRAMES;
// double **IFRAMES;
double **IGFRAMES;
double **OFRAMES;
double **IOFRAMES;
void freeFrameLists2(int fCount){
	for(int i=0;i<fCount;i++){
		free(OFRAMES[i]);
		free(IOFRAMES[i]);
	}
	free(OFRAMES);
	free(IOFRAMES);
	return;
}
void freeFrameLists(int fCount,int ofCount){
	for(int i=0;i<fCount;i++){
		free(FRAMES[i]);
		free(GFRAMES[i]);
		// free(IMPULSE[i]);
		free(IGFRAMES[i]);
	}
	free(FRAMES);
	free(GFRAMES);
	// free(IMPULSE);
	free(IGFRAMES);
	freeFrameLists2(ofCount);
	return;
}
void framing(double *S,int size,int *fcount,int overlap){
	createFrames(S,size,&FRAMES,FSIZE,fcount,overlap);
	return;
}
void framing2(double *S,int size,int *fcount,int overlap){
	createFrames(S,size,&OFRAMES,FSIZE,fcount,overlap);
	return;
}

void initLPCFiles(){
	char filename[1000];
	for(int i=1;i<=LPCORDER;i++){
		sprintf(filename,"LPC_%d_OVERLAP.txt",i);
		resetfile(filename);
		sprintf(filename,"LPC_%d_NONOVERLAP.txt",i);
		resetfile(filename);
		sprintf(filename,"PARCOR_%d_OVERLAP.txt",i);
		resetfile(filename);
		sprintf(filename,"PARCOR_%d_NONOVERLAP.txt",i);
		resetfile(filename);
	}
	return;
}
void soundGenerateIMPULSE(int fCount,int fSize,int overlap){
	IOFRAMES=(double **)malloc(sizeof(double *)*fCount);
	double K[LPCORDER];
	double A[LPCORDER+1];
	double I[fSize];
	double G;
	char file[1000],buffer[1000];
	for(int i=0;i<fCount;i++){
		IOFRAMES[i]=0;
		IOFRAMES[i]=(double *)malloc(sizeof(double)*fSize);
		if(IOFRAMES[i]==0){
			printf("\nNOT ENOUGH MEMORY !!!\n");
			exit(-1);
		}
		G=calc_coeff(OFRAMES[i],K,A,fSize,LPCORDER);
		for(int j=1;j<=LPCORDER;j++){
			sprintf(file,"LPC_%d_OVERLAP.txt",j);
			sprintf(buffer,"%d %lf",i,A[j]);
			addLine(file,buffer);
			sprintf(file,"PARCOR_%d_OVERLAP.txt",j);
			sprintf(buffer,"%d %lf",i,K[j]);
			addLine(file,buffer);
		}
		generateImpulse(I,fSize,F0,G);
		for(int j=0;j<fSize;j++){
			sprintf(buffer,"%lf",I[j]);
			addLine("IMPULSEGAIN.txt",buffer);
		}
		impulseToSignalFIR(A,I,IOFRAMES[i],fSize,LPCORDER);
		// printf("\nCOMPARE FRAMES ----> # frame = %d",i);
		// printArray(FRAMES[i],fSize);
		// printArray(GFRAMES[i],fSize);
		// printf("\n####################################");
	}
	return;
}
void soundGenerate(int fCount,int fSize,int overlap){
	GFRAMES=(double **)malloc(sizeof(double *)*fCount);
	IGFRAMES=(double **)malloc(sizeof(double *)*fCount);
	double K[LPCORDER+1];
	double E[fSize],B[fSize],B2[fSize];
	double I[fSize],A[LPCORDER+1];
	double G;
	char file[1000],buffer[1000];
	for(int i=0;i<fCount;i++){
		GFRAMES[i]=0;
		GFRAMES[i]=(double *)malloc(sizeof(double)*fSize);
		if(GFRAMES[i]==0){
			printf("\nNOT ENOUGH MEMORY !!!\n");
			exit(-1);
		}
		IGFRAMES[i]=0;
		IGFRAMES[i]=(double *)malloc(sizeof(double)*fSize);
		if(IGFRAMES[i]==0){
			printf("\nNOT ENOUGH MEMORY !!!\n");
			exit(-1);
		}
		G=calc_coeff(FRAMES[i],K,A,fSize,LPCORDER);
		// printArray(K,LPCORDER);
		// printf("\nGAIN : %lf",G);
		for(int j=1;j<=LPCORDER;j++){
			sprintf(file,"LPC_%d_NOOVERLAP.txt",j);
			sprintf(buffer,"%d %lf",i,A[j]);
			addLine(file,buffer);
			sprintf(file,"PARCOR_%d_NOOVERLAP.txt",j);
			sprintf(buffer,"%d %lf",i,K[j]);
			addLine(file,buffer);
		}
		generateError(FRAMES[i],K,E,B,B2,fSize,LPCORDER);
		for(int j=0;j<fSize;j++){
			sprintf(buffer,"%lf",E[j]);
			addLine("ERRORFILE.txt",buffer);
		}
		generateSignal(K,E,B,B2,GFRAMES[i],fSize,LPCORDER);
		generateImpulse(I,fSize,F0,G);
		impulseToSignal(K,I,IGFRAMES[i],fSize,LPCORDER,G,F0);
		// printf("\nCOMPARE FRAMES ----> # frame = %d",i);
		// printArray(FRAMES[i],fSize);
		// printArray(GFRAMES[i],fSize);
		// printf("\n####################################");
	}
	return;
}
int isSame(double *A,double *B,int size){
	for(int i=0;i<size;i++){
		if(fabs(A[i]-B[i])>ERROR){
			return 0;
		}
	}
	return 1;
}

int main(int argc,char **argv){
	// system("reset");
	// printf("\nWE ARE HERE !!\n");
	initLPCFiles();
	resetfile("ERRORFILE.txt");
	resetfile("IMPULSEGAIN.txt");
	sscanf(argv[1],"%lf",&argALPHA);
	sscanf(argv[2],"%d",&argOVERLAP);
	sscanf(argv[3],"%d",&argFSIZE);
	sscanf(argv[4],"%d",&argLPCORDER);
	sscanf(argv[5],"%d",&argF0);
	double *S,*X,*Z,*R,*I;
	S=X=Z=R=0;
	S=(double *)malloc(sizeof(double)*MAXSAMPLESIZE);
	X=(double *)malloc(sizeof(double)*MAXSAMPLESIZE);
	Z=(double *)malloc(sizeof(double)*MAXSAMPLESIZE);
	R=(double *)malloc(sizeof(double)*MAXSAMPLESIZE);
	// I=(double *)malloc(sizeof(double)*MAXSAMPLESIZE);

	if(S==0||X==0||Z==0||R==0){
		printf("\nMEMORY ALLOCATION FAILED !!\n");
		exit(-1);
	}

	int size;
	int fCount,ofCount;
	/************** PRE EMPHASIS AND FRAMING ********************/
	textToArray(filename,S,&size);
	// printf("\nORIGINAL SIGNAL :");
	// printArray(S,size);
	preEmphasis(S,X,size,ALPHA);
	// printf("\nPRE EMPHASISED SIGNAL :");
	// printArray(X,size);
	framing(X,size,&fCount,NOOVERLAP);
	// printf("\nFRAMED SIGNAL : ");
	// printFrames(FRAMES,fCount,FSIZE);
	/************************************************************/


	/*************** GENERATE WITH SIGNAL ***********************/
	soundGenerate(fCount,FSIZE,NOOVERLAP);
		/************* FOR ERROR-GENERATED SIGNAL *****/
	frameToSpeech(Z,size,GFRAMES,FSIZE,fCount,NOOVERLAP);
	// printf("\nRE CONSTRUCTED WITH PRE EMPHASIS :");
	// printArray(Z,size);
	removePreEmphasis(Z,R,size,ALPHA);
	// printf("\nFINAL RECONSTRUCTION :");
	// printArray(R,size);
	if(isSame(S,R,size)==1){
		printf("\nSUCCESS IN RECONSTRUCTION FROM ERROR!!");
	}else{
		printf("\nFAILURE IN RECONSTRUCTION FROM ERROR!!");
	}
	dumpArray(efilename,R,size,100);
		/**********************************************/
	
		/************ FOR IMPULSE GENERATED SIGNAL ****/
	
	frameToSpeech(Z,size,IGFRAMES,FSIZE,fCount,NOOVERLAP);
	// printArray(Z,size);
	removePreEmphasis(Z,R,size,ALPHA);
	// // printArray(R,size);
	dumpArray(ifilename,R,size,100);
		/**********************************************/
	/************************************************************/

	
	/***************** LPC USING FIR FILTER **************/
	framing2(X,size,&ofCount,OVERLAP);
	soundGenerateIMPULSE(ofCount,FSIZE,OVERLAP);
	frameToSpeech(Z,size,IOFRAMES,FSIZE,ofCount,OVERLAP);
	removePreEmphasis(Z,R,size,ALPHA);
	dumpArray(impulsefile,R,size,100);
	/*****************************************************/
	
	free(S);
	free(Z);
	free(R);
	free(X);
	// free(I);
	freeFrameLists(fCount,ofCount);
	printf("\n");
	return 0;
}