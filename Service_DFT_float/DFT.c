#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "Signal_float.h"
#include "CosSin_float.h"


float dft(float * Sig, int k){
	int M = 64;
	float Re;
	float Im;
	for (int i =0;i<M;i++){
		int j=i*k%M;
		Re += Sig[i]*TabCos[j];
		Im -= Sig[i]*TabSin[j];
	}
	return (Re*Re) + (Im*Im);
	
}

int main(){
	float res[64]; 
	for(int k = 0; k < 64; k++){
		res[k] = dft(LeSignal,k);
		printf("%f\n", res[k]);
	}
	return 0;
}