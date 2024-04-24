

#include "DriverJeuLaser.h"
#include "ServiceJeuLaser.h"
#include "../Service_DFT_float/DFT.h"
#include "Signal_float.h"
//void hello(){
	//static int a;
	//a++;
//}

short int SotieSon;
void GestionSon_callback(void);
void GestionSon_Start(void);
void GestionSon_Stop(void);
extern int PeriodeSonMicroSec;
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
	ServJeuLASER_Son_Init(PeriodeSonMicroSec, 1, GestionSon_callback);
	//ServJeuLASER_Son_Init(PeriodeSonMicroSec*2756,2,GestionSon_Start);
	
	

//============================================================================	
float res[64]; 
for(int k = 0; k < 64; k++){
		res[k] = dft(LeSignal,k);
	}
	
while	(1)
	{
	}
}




