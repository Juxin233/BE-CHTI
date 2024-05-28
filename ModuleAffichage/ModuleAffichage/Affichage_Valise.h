
/* Fichier devant contenir l'ensemble de fichiers utiles pour le projet LaserQuest
et qui concenent l'affichage sur la valise */
/* mais non disponible en version source pour les �tudiants.						*/

#ifndef _AFFICHAGE_VALISE_H__
#define _AFFICHAGE_VALISE_H__
#include "stm32f10x.h"


/**
	* @brief  Initialise les p�riph�riques n�cessaires � l'affichage sur la Mallette
	*					et g�re la cible active. S'utilise aussi avec les �modules affichages simple (pas de mallette)
  * @note   Utilise TIM1, PA5, PA6 pour les cibles, PC7 � PC9 pour SPI �mul�
	*					 utilise aussi une interruption sut TIM1, prio 8.
	* @param  none
  * @retval None
  */
void Init_Affichage(void);


/**
	* @brief  Pr�pare l'affichage 2 digit sur l'afficheur demand�
  * @note   Exemple : Prepare_Afficheur(2, 99); 
	*         pr�pare l'affichage de la valeur 99 sur l'afficheur n�2
	* 			  L'action est diff�r�e � l'ex�cution de Mise_A_Jour_Afficheurs_LED()
	* @param  char Aff : de 1 � 4 ; char Valeur de 0 � 99
  * @retval None
  */
void Prepare_Afficheur(char Aff, char Valeur);



void Prepare_Set_Point_Unite(char Aff);
void Prepare_Clear_Point_Unite(char Aff);


/**
	* @brief  Pr�pare l'allumage de la LED demand�e
  * @note   Exemple : Prepare_Set_LED(LED_Cible_2); 
	*         pr�pare l'allumage de la LED correspondant � la cible n�2
	*					L'action est diff�r�e � l'ex�cution de Mise_A_Jour_Afficheurs_LED()
	* @param  voir #define ci-dessous
  * @retval None
  */
void Prepare_Set_LED(char LED);
void Prepare_Clear_LED(char LED);


/**
	* @brief  Effectue l'action d'�criture dans le module d'affichage
	*					� partir de tout ce qui a �t� pr�par� auparavant.
  * @note   
	* @param  None
  * @retval None
  */
void Mise_A_Jour_Afficheurs_LED(void);

/**
	* @brief  Sp�cifie le capteut actif, � savoir celui effectivement reli�
	*					aux sorties disponibles sur la malette
  * @note   Exemple : Choix_Capteur(1)        
	* @param  1 � 4
  * @retval None
  */
void Choix_Capteur(char Capteur);
// define utile pour la fonction Prepare_Set_LED et Prepare_Clear_LED
#define LED_LCD_R 5
#define LED_LCD_V  4
#define LED_Cible_4 3
#define LED_Cible_3 2
#define LED_Cible_2 1
#define LED_Cible_1 0



#endif

