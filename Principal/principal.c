

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

/* Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers */
CLOCK_Configure();

/* Configuration du son (voir ServiceJeuLaser.h) 
 Ins�rez votre code d'initialisation des parties mat�rielles g�rant le son ....*/	
ServJeuLASER_Son_Init(PeriodeSonMicroSec, 1, GestionSon_callback);

	
	

//============================================================================	
	
	
while	(1)
	{
	}
}




