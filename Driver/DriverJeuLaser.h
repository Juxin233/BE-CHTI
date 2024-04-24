/**
 * Bibliotheque DriverJeuLaser (ancienne gassp72 adaptée 2021 - TR)
 *
 * GPIO - ADC - Sequenceur - System Timer - PWM - 72 MHz
 * Modifs :
 * enlèvement de tout ce qui est inutile dans le .h 
 * ajout de fonctions GPIO dans le .c pour utilisation en ASM ou en C :
 *  - GPIOA_Set(char Broche), GPIOB_Set(char Broche), GPIOC_Set(char Broche)
 *  - GPIOA_Clear(char Broche), GPIOB_Clear(char Broche), GPIOC_Clear(char Broche)
 * 
 * ajout d'une fonction qui impose une valeur de PWM (TIM3_CCR3)
 * PWM_Set_Value_On_TIM3_C3( int Val) 
 * permet en ASM ou en C de fixer la valeur de PWM 
 
 * Ajout de commentaires
 
 */
#ifndef DRIVERJEULASER_H__
#define DRIVERJEULASER_H__

#include "stm32f10x.h"

//**********************************************************************************************************
//---------------------          CONFIGURATION CLOCK DU STM32         --------------------------------------
//**********************************************************************************************************

/**
	* @brief  Configure l'ensemble des horloges du uC
  * @note   horloge systeme (config statique a 72 MHz pour le STM32F103)
	* @param  None
  * @retval None
  */
void CLOCK_Configure(void);










//**********************************************************************************************************
//---------------------          LES TIMERS GENERAL PURPOSE TIM1 à TIM 4      ------------------------------
//**********************************************************************************************************

/**
	* @brief  Configure un Timer TIM1 à TIM4 avec une périodicité donnée
  * @note   L' horloge des 4 timers a une fréquence de 72MHz
	* @param  *Timer = TIM1 ou TIM2 ou TIM3 ou TIM4
	* @param  Durée_ticks : nombre de pas (tick) comptés à 72 MHz pour faire déborder le timer 
	*         La période de débordement du Timer est donc T = Durée_ticks * Tck, avec Tck = 1/72 000 000
  * @retval None
  */
void Timer_1234_Init_ff( TIM_TypeDef *Timer, u32 Duree_ticks );

/**
 * Macros de base pour utiliser les timers
 */
 // bloque le timer
#define Bloque_Timer(Timer) Timer->CR1=(Timer->CR1)&~(1<<0)
// Lance timer
#define Run_Timer(Timer) Timer->CR1=(Timer->CR1)|(1<<0)



/**
	* @brief  Associe une fonction d'interruption (callback) lors du débordement d'un timer
  * @note   
	* @param  *Timer = TIM1 ou TIM2 ou TIM3 ou TIM4
	* @param  Prio : niveau de priorité de l'interruption (0 -> priorité max, 15 ->  priorité min)
	* @param  IT_function : le nom de la fonction Callback à appeler lors de l'interruption
  * @retval None
  */
void Active_IT_Debordement_Timer( TIM_TypeDef *Timer, char Prio, void (*IT_function)(void) );











//*********************************************************************************************************
//---------------------               PWM   TIM1 to TIM 4                   ------------------------------
//*********************************************************************************************************

/**
	* @brief  Configure un timer en PWM 
  * @note   
	* @param  *Timer = TIM1 ou TIM2 ou TIM3 ou TIM4
	* @param  voie : un des 4 canaux possibles 1 à 4.
	* @param  Periode_ticks : nombre de pas (tick) comptés à 72 MHz pour faire déborder le timer 
	*         La période de débordement du Timer est donc T = Durée_ticks * Tck, avec Tck = 1/72 000 000
  * @retval Retourne la période  en tick (normalement la même que le param d'entrée sauf si PSC utilisé
  */
unsigned short int PWM_Init_ff( TIM_TypeDef *Timer, char Voie, u32 Periode_ticks );



/**
	* @brief  Fixe une valeur de PWM, Val, en tick horloge. La rapport cyclique effectif
	* est donc : rcy = Thaut_ticks / Periode_ticks
  * @note   spécifique Jeu Laser, PWM liée exclusivement au TIM3, chan3
	* @param  Thaut_ticks : durée de l'état haut d'une impulsion en Ticks
  * @retval None
  */
void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks);









//**********************************************************************************************************
//---------------------          LE SYSTICK TIMER, Part of Cortex M3          ------------------------------
//**********************************************************************************************************

/**
	* @brief  Configure le timer Systick avec une périodicité donnée
  * @note   Ce timer ne peut servir qu'à créer des temporisations ou générer des interruption
	*         ce n'est pas à proprement parler un périphérique, il fait partie du Cortex M3
	*         Ce timer est un 24 bits 
	* @param  Periode_ticks : nombre de pas (tick) comptés à 72 MHz pour établir la périodicité
	*          La période de débordement du Timer est donc T = Durée_ticks * Tck, avec Tck = 1/72 000 000
  * @retval None
  */
void Systick_Period_ff( unsigned int Periode_ticks );



/**
	* @brief  Associe une fonction d'interruption (callback) lors du débordement du Systick
  * @note   
	* @param  Prio : niveau de priorité de l'interruption (0 -> priorité max, 15 ->  priorité min)
	* @param  IT_function : le nom de la fonction Callback à appeler lors de l'interruption
  * @retval None
  */
void Systick_Prio_IT( char Prio, void (*Systick_function)(void) );


/**
 * Macros de base pour utiliser le Systick 
 */
#define  SysTick_On ((SysTick->CTRL)=(SysTick->CTRL)|1<<0)
#define  SysTick_Off ((SysTick->CTRL)=(SysTick->CTRL)& ~(1<<0))
#define  SysTick_Enable_IT ((SysTick->CTRL)=(SysTick->CTRL)|1<<1)
#define  SysTick_Disable_IT ((SysTick->CTRL)=(SysTick->CTRL)& ~(1<<1))











//**********************************************************************************************************
//---------------------           ANALOG INPUT  ADC & DMA                     ------------------------------
//**********************************************************************************************************

/**
	* @brief  Active l'ADC du STM32, configure la durée de prélèvement de l'échantillon (temps
	* de fermeture du switch d'acquisition
  * @note   
	* @param  ADC : précise de quel ADC il s'agit, ADC1 ou ADC2
	* @param  Duree_Ech_ticks : dirée de fermeture du switch d'échantillonnage en Tick d'horloge CPU
	*         exemple pour 1µs on choisira 72.
  * @retval Nombre de Tick réellement pris en compte
  */
unsigned int Init_TimingADC_ActiveADC_ff( ADC_TypeDef * ADC, u32 Duree_Ech_ticks );


/**
	* @brief  Sélectionne la voie à convertir
  * @note   Attention, la voie va de 0 à 15 et n'est pas directement lié au n°de GPIO
	* @param  ADC : précise de quel ADC il s'agit, ADC1 ou ADC2
	* @param  Voie_ADC : 1 à 15
  * @retval None
  */
void Single_Channel_ADC( ADC_TypeDef * ADC, char Voie_ADC );





/**
	* @brief  Permet lier le déclenchement au débordement d'un timer, spécifie également
	*         la période de débordement du timer 
  * @note   pas besoin de régler le timer avec une autre fonction dédiée timer
	* @param  ADC : précise de quel ADC il s'agit, ADC1 ou ADC2
	* @param  Source : indique le timer qui déclenche l'ADC choix dans les define ci-dessous
	* @param	Periode_ticks : nombre de pas (tick) comptés à 72 MHz pour faire déborder le timer 
	*         La période de débordement du Timer est donc T = Durée_ticks * Tck, avec Tck = 1/72 000 000
  * @retval None
  */

// param pour Source :
#define TIM1_CC1 0
#define TIM1_CC2 1
#define TIM1_CC3 2
#define TIM2_CC2 3
#define TIM4_CC4 5
void Init_Conversion_On_Trig_Timer_ff( ADC_TypeDef * ADC, char Source, u32 Periode_ticks );






/**
	* @brief  Permer de lier l'ADC à un tableau en RAM pour une DMA 
  * @note   
	* @param  Circ : circular. Si '0', en fin de DMA le ptr d'@ reste inchangé
	*         si '1' le ptr d'@ se recale à celle du début.
	* @param  Ptr_Table_DMA : contient l'@ de début de zone RAM à écrire
	* @retval None
  */
void Init_ADC1_DMA1(char Circ, short int *Ptr_Table_DMA);





/**
	* @brief  Lance une DMA sur le nombre de points spécifie. Les resultats seront stockes
	*         dans la zone de RAM écrite est indiquée lors de l'appel de la fonction  Init_ADC1_DMA1 
  * @note   
	* @param  NbEchDMA est le nombre d'échantillons à stocker.
	* @retval None
  */
void Start_DMA1( u16 NbEchDMA );

// arret DMA
#define  Stop_DMA1 DMA1_Channel1->CCR =(DMA1_Channel1->CCR) &~0x1;


/**
	* @brief  Attend la fin d'un cycle de DMA. la duree depend de la periode d'acquisition 
	* et du nombre d'echantillons
  * @note   fonction d'attente (bloquante) 
	* @param  None
	* @retval None
  */
void Wait_On_End_Of_DMA1(void);








//**********************************************************************************************************
//---------------------                   GPIO                                ------------------------------
//**********************************************************************************************************

/**
	* @brief  Initialisation d'un GPIO (A à C), pin x. 
  *  			peut être configuré :
	*  			-> Input ou output
	*       -> architecture technologique (push-pull, open drain...)
	
  * @note   
	* @param  Port : GPIOA, GPIOB, GPIOC
	* @param  Broche : 0 à 15
	* @param  Sens : INPUT ou OUTPUT
	* @param  Techno : voir define ci dessous
	* @retval 1 erreur, 0 si OK
  */

// Sens
#define INPUT   'i'
#define OUTPUT  'o'

// Techno pour pin en entrée (INPUT)
#define ANALOG              0
#define INPUT_FLOATING      1
#define INPUT_PULL_DOWN_UP  2

// Techno pour pin en sortie (OUTPUT)
#define OUTPUT_PPULL    0
#define OUTPUT_OPDRAIN  1
#define ALT_PPULL       2
#define ALT_OPDRAIN     3

// Exemple :
// Port_IO_Init(GPIOB, 8, OUTPUT, OUTPUT_PPULL);
// Place le bit 8 du port B en sortie Push-pull
char GPIO_Configure(GPIO_TypeDef * Port, int Broche, int Sens, int Techno);


/**
	* @brief  Mise à 1 d'une broche GPIO	
  * @note   Une fonction par GPIO
	* @param  Broche : 0 à 15
	* @retval None
  */

void GPIOA_Set(char Broche);
void GPIOB_Set(char Broche);
void GPIOC_Set(char Broche);



/**
	* @brief  Mise à 0 d'une broche GPIO	
  * @note   Une fonction par GPIO
	* @param  Broche : 0 à 15
	* @retval None
  */

void GPIOA_Clear(char Broche);
void GPIOB_Clear(char Broche);
void GPIOC_Clear(char Broche);


#endif


