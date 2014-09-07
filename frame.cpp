#ifndef FRAME
#define FRAME
#include <stdio.h>
#include <stdlib.h>
#include "fileio.c"


struct frame{
	double *f;
	struct frame *next;
};
typedef struct frame frame;

struct frameList{
	frame *head;
	int fCount;
	int fSize;
};
typedef struct frameList frameList;

void initFrameList(frameList *f,int fSize){
	f->head=0;
	f->fCount=0;
	f->fSize=fSize;
	return;
}
void insertFrame(frameList *f,double *S,int end,int i,int j){
	if((j-i+1)!=(f->fSize)){
		printf("\nFRAME SIZE INDEX MISSMATCH!! j=%d i= %d FSIZE = %d",j,i,f->fSize);
		exit(-1);
	}
	frame *temp;
	temp=f->head;
	f->head=(frame *)malloc(sizeof(frame));
	f->head->next=temp;
	double *x;
	x=NULL;
	x=(double *)malloc(sizeof(double)*f->fSize);
	if(x==NULL){
		printf("\nCANT ALLOCATE SPACE FOR FRAME !!");
		exit(-1);
	}
	(f->fCount)++;
	f->head->f=(x);
	int l=0;
	for(int k=i;k<=j;k++){
		if(k>end){
			f->head->f[l]=0;
		}else{
			f->head->f[l]=S[k];
		}
		l++;
	}
	return;
}
void frameListToArray(frameList *f,double **frames){
	int fCount=f->fCount;
	frame *temp=f->head;
	for(int i=fCount-1;i>=0;i--){
		if(temp==NULL){
			printf("\nGOING TO READ NULL DATA !!");
			exit(-1);
		}
		// printf("\n************************");
		for(int j=0;j<f->fSize;j++){
			// printf("\ntemp = %lf j = %d fsize = %d",temp->f[j],j,f->fSize);
			frames[i][j]=temp->f[j];
		}
		temp=temp->next;
	}
	return;
}
void clearFrameList(frameList *f){
	frame *temp=f->head;
	if(temp==NULL){
		return;
	}
	frame *xtemp;
	while(temp!=NULL){
		xtemp=temp->next;
		free(temp->f);
		free(temp);
		temp=xtemp;
	}
	return;
}
void textToArray(const char *filename,double *S,int *size){
	int endflag;
	char buffer[100];
	FILE *f=initializeFileRead(filename,&endflag);
	int i=0;
	while(1){
		readLine(f,buffer,&endflag);
		if(buffer[0]=='\0'){
			break;
		}
		sscanf(buffer,"%lf",S+i);
		i++;
	}
	*size=i;
	fclose(f);
	return;
}
void printArray(double *S,int size){
	printf("\n**********************\n");
	for(int i=0;i<size;i++){
		printf("{%d > %lf} ",i,S[i]);
	}
	printf("\nSIZE  = %d",size);
	printf("\n**********************");
	return;
}
void preEmphasis(double *S,double *X,int size,double alpha){
	// X is already asssumed to be declared
	double *Y=(double *)malloc(sizeof(double)*size);
	for(int i=0;i<size;i++){
		Y[i]=S[i];
	}
	X[0]=Y[0];
	for(int i=1;i<size;i++){
		X[i]=Y[i]-(alpha*Y[i-1]);
	}
	free(Y);
	return;
}
void removePreEmphasis(double *X,double *S,int size,double alpha){
	double *Y=(double *)malloc(sizeof(double)*size);
	for(int i=0;i<size;i++){
		Y[i]=X[i];
	}
	for(int i=1;i<size;i++){
		Y[i]=Y[i]+(alpha*Y[i-1]);
		S[i]=Y[i];
	}
	S[0]=Y[0];
	free(Y);
	return;
}
void createFrames(double *S,int size,double ***F,int fSize,int *fCount,int overlap){
	if(fSize<=overlap){
		printf("\nERROR FRAME SIZE = %d OVERLAP = %d",fSize,overlap);
		exit(-1);
	}
	int i,j,k,end;
	end=size-1;
	frameList f;
	initFrameList(&f,fSize);
	i=0;
	j=fSize-1;
	while(1){
		// void insertFrame(frameList *f,double *S,int end,int i,int j)
		insertFrame(&f,S,end,i,j);
		if(j>=end){
			break;
		}
		i=i+fSize-overlap;
		j=i+fSize-1;
	}
	*F=(double **)malloc(sizeof(double *)*(f.fCount));
	double **frames=*F;
	for(int i=0;i<f.fCount;i++){
		frames[i]=0;
		frames[i]=(double *)malloc(sizeof(double)*f.fSize);
		if(frames[i]==0){
			printf("\nNOT ENOUGH MEMORY !!");
			exit(-1);
		}
	}
	*fCount=f.fCount;
	// printf("\nFRAMING DONE IN LINKED LIST \n");
	frameListToArray(&f,frames);
	clearFrameList(&f);
	return;
}
void printFrames(double **f,int fCount,int fSize){
	printf("\n#### SIGNAL PER FRAME **************");
	printf("\n#### FRAME LEN = %d\tFRAME COUNT = %d",fSize,fCount);
	for(int i=0;i<fCount;i++){
		printf("\n## FRAME <%d> ***********\n",i);
		for(int j=0;j<fSize;j++){
			printf("%lf ",f[i][j]);
		}
		printf("\n***********************");
	}
	printf("\n********************************");
	return;
}
void frameToSpeech(double *S,int size,double **frame,int fSize,int fCount,int overlap){
	for(int i=0;i<size;i++){
		S[i]=0;
	}
	int k=0;
	for(int i=0;i<fCount;i++){
		for(int j=0;j<fSize;j++){
			if(k>=size){
				break;
			}
			S[k]=S[k]+frame[i][j];
			k++;
		}
		k=k-overlap;
	}
	return;
}
#endif