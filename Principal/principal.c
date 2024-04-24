

#include "DriverJeuLaser.h"
#include "ServiceJeuLaser.h"

//void hello(){
	//static int a;
	//a++;
//}

short int SotieSon;
void GestionSon_callback(void);

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
ServJeuLASER_Son_Init(PeriodeSonMicroSec, 1, GestionSon_callback);

	
	

//============================================================================	
	
	
while	(1)
	{
	}
}




