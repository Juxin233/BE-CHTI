#ifndef SERVICEJEULASER_H
#define SERVICEJEULASER_H


#define Timer_Te_Son TIM4
#define Timer_PWM	TIM3





/**
	* @brief  Configure tous les éléments matériels (périphériques) qui gèrent le son 
						Une fois la fonction exécutée, les périphériques ci-dessous sont lancés, l'interruption
						qui appelle périodiquement le callback est validée.
  * @note   Periphériques utilisés :
						- TIM4 : il provoque l'appel du callback à intervalle de tps régulier, Te (Periode_Te_us)
						- TIM3 : il génère le signal PWM de fréquence 100kHz. La valeur numérique "à convertir
						en analogique" est passée par la fonction dédiée accessible via le header DriverJeuLaser.h
						(void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks)).
						- La pin par laquelle sort le signal PWM est PB.0 (configuré en alt PushPull).
						
		* @param  int Periode_Te_us : intervalle de temps donné en µs entre deux appels consécutifs du callback
							prio : niveau de priorité de l'interruption qui lance le callback. 
											0 = priorité maxi
										 15 = priorité mini
							IT_function : nom de la fonction qui est appelée à échéance du compteur TIM4, cad
														toutes les Periode_Te_us µs.
	
  * @retval None
  */
void ServJeuLASER_Son_Init(int Periode_Te_us, char prio, void (*IT_function)(void));





/**
	* @brief  Convertit un entier en une valeur "analogique" proportionnelle. 
						Le convertisseur est une PWM (non un DAC). La fréquence de PWM est supposée réglée à 100kHz. 
						La plage de valeurs possibles en entrée s'étend de 0 à 719 correspondant proportionnellement 
						à un rapport cyclique de 0 à 100%
						
  * @note   ATTENTION ! L'utilisation de cette fonction suppose que l'initialisation a déjà été exécutée
						(cf . fonction ServJeuLASER_Son_Init
						
	* @param  EchSon : valeur à convertir "en analogique"
	
  * @retval None
  */
void ServJeuLASER_WritePWMSoundVal(unsigned short int EchSon);







/**
	* @brief  Configure le timer Systick pour qu'il génère une interruption périodique.
  * @note   Lorsque la fonction est terminée, le timer est lancé, les interruptions sont validées
						
	* @param  int Periode_Te_us : intervalle de temps donné en µs entre deux appels consécutifs du callback
						prio : niveau de priorité de l'interruption qui lance le callback. 
											0 = priorité maxi
										 15 = priorité mini
						IT_function : nom de la fonction qui est appelée à échéance du compteur Systick, cad
													toutes les Periode_Te_us µs.
	
  * @retval None
  */
void ServJeuLASER_Systick_IT_Init(int Periode_Te_us, char prio, void (*IT_function)(void));



/**
	* @brief  Configure l'ensemble ADC, DMA pour un échantillonnage à 320kHz, 64 échantillons
  * @note    Periphériques utilisés :
						- TIM2 : cadence l'ADC à 320kHz
						- ADC1 voie 2 : il opère la conversion analogique numérique [0-3.3V] -> [0 -4095] (12 bits !)
						- la DMA configurée pour prélever 64 échantillons puis s'arrête
						
	* @param  DMA_Tab : l'adresse de la table qui va recevoir les 64 échantillons
  * @retval _	
  */


void ServJeuLASER_ADC_DMA(short int * DMA_Tab);


/**
	* @brief  Lance l'acquisition d'un bloc de 64 éléments	
	* @note 	la fonction est BLOQUANTE pendant 200µs
	* @param  _
  * @retval _
  */


void ServJeuLASER_StartDMA(void);

#endif
