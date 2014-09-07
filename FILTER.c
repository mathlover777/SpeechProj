#ifndef FILTER
#define FILTER


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generateError(double* S, double* k, double* E1, double* B1,double* B2, int L, int p){

	int i,j;
	double** E=(double**)malloc((p+1)*sizeof(double*));
	double** B=(double**)malloc((p+1)*sizeof(double*));
	for(i=0;i<p+1;i++){
		// for(i=0;i<20;i++){
		// error 20 ---> p
       E[i]=(double*)malloc(L*sizeof(double));
       B[i]=(double*)malloc(L*sizeof(double));
       
    }
	//printf("In generror");
	for(j=0;j<L;j++){
		E[0][j]=S[j]; 
		B[0][j]=S[j];
	}
	B2[0]=B[0][L-1];
	for(i=1;i<=p;i++){
		E[i][0]=E[i-1][0];
		B[i][0]=-(k[i]*E[i-1][0]);
		for(j=1;j<L;j++){
			E[i][j]=E[i-1][j]-(k[i]*B[i-1][j-1]);
			B[i][j]=B[i-1][j-1]-(k[i]*E[i-1][j]);
		}
		B2[i]=B[i][L-1];
	}
	for(j=0;j<L;j++){
		E1[j]=E[p][j]; 
		B1[j]=B[p][j];
	}
	for(int i=0;i<p+1;i++){
		free(E[i]);
		free(B[i]);
	}
	free(E);
	free(B);
	return;
}

void generateSignal(double *k, double *E1, double *B1,double *B2,double *S1,int L, int p){

	int i,j;
	double** E=(double**)malloc((p+1)*sizeof(double*));
	double** B=(double**)malloc((p+1)*sizeof(double*));
	if(E==0||B==0){
		printf("\nNOT ENOUGH MEMORY !!\n");
		exit(-1);
	}
	for(i=0;i<p+1;i++){
		// for(i=0;i<20;i++){
       	E[i]=(double*)malloc(L*sizeof(double));
       	B[i]=(double*)malloc(L*sizeof(double));
       	if(E[i]==0||B[i]==0){
       		printf("\nNOT ENOUGH MEMORY !!\n");
       		exit(-1);
       	}
       
    }
    for(j=0;j<L;j++){
			E[p][j]=E1[j];
			B[p][j]=B1[j];
	}
	for(i=p-1;i>=0;i--){
		
		for(j=0;j<L;j++){
			E[i][j]=(E[i+1][j]+(k[i+1]*B[i+1][j]))/(1-k[i+1]*k[i+1]);

		}
		for(j=0;j<L-1;j++){
			B[i][j]=(k[i+1]*E[i+1][j+1]+B[i+1][j+1])/(1-k[i+1]*k[i+1]);
		}
		B[i][L-1]=B2[i];
		

	}
	for(j=0;j<L;j++){
		S1[j]=E[0][j];	
	}
	for(int i=0;i<p+1;i++){
		free(E[i]);
		free(B[i]);
	}
	free(E);
	free(B);
	return;
}
void generateImpulse(double* S, int L, int F, double G){
	int i;
	for(i=0;i<L;i++){
		S[i]=0;
	}
	for(i=0;i<L;i+=F){
		S[i]=G;
	}
	return;
}
void impulseToSignal(double* k, double* I, double* S, int L, int p, double G, int F){

	int i,j;
	double * B=(double*)malloc((p+1)*sizeof(double));
	double * I1=(double*)malloc((L)*sizeof(double));
	for(i=0;i<L;i++){
		I1[i]=I[i];
	}
	for(i=0;i<=p;i++){
		if(L%F==0){
			B[i]=G;
		}
		else{
			B[i]=0;
		}
	}
	generateSignal(k,I,I1,B,S,L,p);
	free(I1);
	free(B);
	return;
}
// void main(){

// 	double S[20];
// 	int i;
// 	generateImpulse(S,20,2,0.645);

// 	for(i=0;i<20;i++){
// 		printf("S[%d]=%lf\n",i,S[i]);
		
// 	}
// 	scanf("%d",&i);
// }
// int main(){
    
//     int i,j;

// 	double S[]={1.2,2.3,2.4,3.5,4.6,5.6,3.12,8.3,3.9,7.5,0,1.2,2.4,3,6,4.8,2.5,2.6,9.8,12.5,23.6};
// 	double k[]={0,0.68,0.13,0.12,0.26,0.04,-0.07,0.03,-0.1,0.14,0.24,-0.05,0.11,-0.17,-0.06,-0.13,-0.13};
// 	double S1[20];
// 	double E[20];
// 	double B[20];            
// 	double B2[20];
// 	//double S1[20];
	
// 	//printf("Calling\n");
// 	generateError(S,k,E,B,B2,20,16);
		
	
// 	generateSignal(k,E,B,B2,S1,20,16);
// 	for(j=0;j<20;j++){
// 		printf("S[%d]=%lf	S1[%d]=%lf\n",j,S[j],j,S1[j]);

// 	}
// 	scanf("%d",&j);
// }

#endif