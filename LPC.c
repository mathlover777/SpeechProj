#ifndef LPC
#define LPC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



double R_calc(double* S, int L, int k){

	int i;
	if(k<0 || k>L-1)
		return 0.0;
	double R=0.0;
	for(i=0;i<L+k;i++){
		R=R+S[i]*S[i+k];
	}
	return R;
}	


double calc_coeff(double* S, double *k, double* a1, int L, int p){

	double *R=(double*)malloc((p+1)*sizeof(double));
	double *E=(double*)malloc((p+1)*sizeof(double));
	double *S1=(double*)malloc((L+p)*sizeof(double));
	
	double a[20][20];

	int i,j;
	double temp;
	double G,R1;

	for(i=0;i<L;i++){
		S1[i]=S[i];
	}
	for(i=L;i<L+p;i++){
		S1[i]=0;
	}

	for(i=0;i<=p;i++){
		R[i]=R_calc(S1,L,i);
	}

	for(i=1;i<=p;i++){
		R[i]=R[i]/R[0];
		// printf("R[%d]=%lf\n",i,R[i]);
	}
	R1=R[0];
	R[0]=1;

	E[0]=R[0];
	k[0]=0;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			a[i][j]=0;
		}
	}

	// printf("Done\n");
	for(i=1;i<=p;i++){

		temp=0.0;
		for(j=1;j<i;j++){
			temp=temp+a[i-1][j]*R[i-j];
		}
		k[i]=(R[i]-temp)/E[i-1];
		a[i][i]=k[i];
		for(j=1;j<i;j++){
			a[i][j]=a[i-1][j]-(k[i]*a[i-1][i-j]);
		}
		E[i]=(1-k[i]*k[i])*E[i-1];

	}

	
	for(i=0;i<=p;i++){
		// printf("a[%d]=%lf\n",i,a[p][i]);
		a1[i]=a[p][i];
	}

	G=R1;
	for(i=1;i<=p;i++){
		G=G*(1-k[i]*k[i]);
	}
	G=sqrt((G));
	// printf("R[0]=%lf",R1);
	// printf("Gain:%lf\n",G);

	free(R);
	free(E);
	free(S1);
	return G;
}
void impulseToSignalFIR(double* a, double* I, double* S, int L, int p){

	double* I1=(double*)malloc((L+p)*sizeof(double));
	int i,j;
	double temp;

	for(i=0;i<p;i++){
		I1[i]=0;
	}
	for(i=p;i<L+p;i++){
		I1[i]=I[i-p];
	}
	for(i=0;i<L;i++){
		temp=0;
		for(j=1;j<=p;j++){
			temp=temp+(a[j]*I1[i+p-j]);
		}
		S[i]=I1[i+p]-temp;
		}
    free(I1);
    return;
}



#endif