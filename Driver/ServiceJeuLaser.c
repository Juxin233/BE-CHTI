#include "ServiceJeuLaser.h"
#include "DriverJeuLaser.h"
/**
	* @brief  voir.h	
	* @note 	voir.h	
	* @param  voir.h	
  * @retval voir.h	
  */


void ServJeuLASER_Son_Init(int Periode_Te_us, char prio, void (*IT_function)(void))
{
	u32 Duree_ticks;
	Duree_ticks = Periode_Te_us * 72;
	Timer_1234_Init_ff( Timer_Te_Son,Duree_ticks);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	PWM_Init_ff( TIM3, 3, 720);
	Active_IT_Debordement_Timer( Timer_Te_Son, prio, IT_function);	
}


/**
	* @brief  voir.h	
	* @note 	voir.h	
	* @param  voir.h	
  * @retval voir.h	
  */
void ServJeuLASER_WritePWMSoundVal(unsigned short int EchSon)
{
	TIM3->CCR3= EchSon;
}



/**
	* @brief  voir.h	
	* @note 	voir.h	
	* @param  voir.h	
  * @retval voir.h	
  */
void ServJeuLASER_Systick_IT_Init(int Periode_Te_us, char prio, void (*IT_function)(void))
{
	u32 Duree_ticks;
	Duree_ticks = Periode_Te_us * 72;
	Systick_Period_ff(Duree_ticks);
	Systick_Prio_IT(prio,IT_function );
	SysTick_On;
	SysTick_Enable_IT;
}


/**
	* @brief  voir.h	
	* @note 	voir.h	
	* @param  voir.h	
  * @retval voir.h	
  */


void ServJeuLASER_ADC_DMA(short int * DMA_Tab)
{
	Init_TimingADC_ActiveADC_ff( ADC1, 72);
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, DMA_Tab);
}



/**
	* @brief  voir.h	
	* @note 	voir.h	
	* @param  voir.h	
  * @retval voir.h	
  */


void ServJeuLASER_StartDMA()
{
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
}
