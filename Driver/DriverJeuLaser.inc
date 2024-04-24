
; Bibliotheque DriverJeuLaser (ancienne gassp72 adaptée 2021 - TR)
; Accès en aux fonctions suivantes :
; GPIO :
; GPIOA_Set(char Broche), GPIOB_Set(char Broche), GPIOC_Set(char Broche)
; GPIOA_Clear(char Broche), GPIOB_Clear(char Broche), GPIOC_Clear(char Broche)
  
; PWM :
;/**
;	* @brief  Fixe une valeur de PWM, Val, en tick horloge. La rapport cyclique effectif
;	* est donc : rcy = Thaut_ticks / Periode_ticks
; * @note   spécifique Jeu Laser, PWM liée exclusivement au TIM3, chan3
;	* @param  Thaut_ticks : durée de l'état haut d'une impulsion en Ticks
;  * @retval None
; */

;void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks);
	import PWM_Set_Value_TIM3_Ch3



;/**
;	* @brief  Mise à 1 d'une broche GPIO	
;  * @note   Une fonction par GPIO
;	* @param  Broche : 0 à 15
;	* @retval None
; */

;void GPIOA_Set(char Broche);
	import GPIOA_Set

;void GPIOB_Set(char Broche);
	import GPIOB_Set

;void GPIOC_Set(char Broche);
	import GPIOC_Set



;/**
;	* @brief  Mise à 0 d'une broche GPIO	
;  * @note   Une fonction par GPIO
;	* @param  Broche : 0 à 15
;	* @retval None
;  */

;void GPIOA_Clear(char Broche);
	import GPIOA_Clear

;void GPIOB_Clear(char Broche);
	import GPIOB_Clear

;void GPIOC_Clear(char Broche);
	import GPIOC_Clear

	end
