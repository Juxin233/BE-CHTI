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
