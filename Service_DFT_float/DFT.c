#include <stdio.h>
#include <stdlib.h>
#include "CosSin_Fract_1_15.h"



unsigned int dft(short * Sig, short k){
	int M = 64;
	long long  Re=0; //64 bits
	long long	 Im=0; //64 bits
	for (int i =0;i<M;i++){
		short j=(i*k)%M;
		Re += Sig[i]*TabCos[j];// Sig //4_12 *Cos//1_15 -> Re //5_27
		Im -= Sig[i]*TabSin[j];// Sig //4_12 *Cos//1_15 -> Im //5_27
	}
	//Re*Re/5_27*5_27-> 10_54 >>32 -> 10_22 
	return ((Re*Re + Im*Im)>>32);
}

