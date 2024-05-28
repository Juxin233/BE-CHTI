
#include <stdio.h>
#include <stdlib.h>
#include "DriverJeuLaser.h"
#include "ServiceJeuLaser.h"
#include "DFT.h"
#include "Signal_4_12.h"
#include "Affichage_Valise.h"
#define SEUIL 0x0000918B
//void hello(){
	//static int a;
	//a++;
//}

short int SotieSon;
void GestionSon_callback(void);
void GestionSon_Start(void);
void GestionSon_Stop(void);
extern int PeriodeSonMicroSec;
unsigned int res[64]={0};
short int buffer[64]={0};
int scores[6]={0};
char joueur[6];
unsigned int dftTab[6]={0};
char Capteur;
int dejatir[6]={0};


void DMAandDFT(void){
	ServJeuLASER_StartDMA();
	for(int k=0;k<64;k++){
		res[k]=dft(buffer,k);
	}
	
	dftTab[0]=dft(buffer,17);
	dftTab[1]=dft(buffer,18);
	dftTab[2]=dft(buffer,19);
	dftTab[3]=dft(buffer,20);
	dftTab[4]=dft(buffer,23);
	dftTab[5]=dft(buffer,24);
	
	for(int i = 0; i < 6; i++){
		if(dftTab[i]>SEUIL){
			if(dejatir[i]==0){
				GestionSon_Start();
				scores[i]++; 
				dejatir[i]++;
			}
		}else{
			dejatir[i]=0;
		}
		printf("Le score du joueur %c est : %d", scores[i], joueur[i]);
		
		//Choix_Capteur(Capteur);
		
	}
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

/* Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers */
CLOCK_Configure();

/* Configuration du son (voir ServiceJeuLaser.h) 
 Insérez votre code d'initialisation des parties matérielles gérant le son ....*/	
	//GestionSon_Start();
	//GestionSon_Stop();
	ServJeuLASER_ADC_DMA(buffer);
	ServJeuLASER_Son_Init(PeriodeSonMicroSec, 0, GestionSon_callback);
	//ServJeuLASER_Son_Init(PeriodeSonMicroSec*2756,2,GestionSon_Start);
	ServJeuLASER_Systick_IT_Init(5000, 1, DMAandDFT);
	
	// Gestion de l'affichage : 
	//ServJeuLASER_Systick_IT_Init(5000, 1, DMAandDFT);
	
	
	
	
	

//============================================================================	


	
while	(1)
	{
	}
}



