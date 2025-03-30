/*
 * Tempe.c
 *
 *  Created on: Oct 17, 2024
 *      Author: pc
 */

#include "adc.h"
#include "Tempe.h"
#include <stdint.h>


//#define TCAL_1C *(uint16_t*)(0x1FF1E820)
//#define TCAL_2C *(uint16_t*)(0x1FF1E840)
#define VCAL_C *(uint16_t*)(0x1FF1E860)
#define lun 100
uint16_t DATA;
uint32_t DATAA_T[lun];
uint32_t DATAA_V;

//unsigned int n=0;
unsigned int i=0;
unsigned int MISURA=0;


void inizializzo_ADC(void) {
	ADC3->SQR1=0;
	ADC3->SQR1|=(0<<ADC_SQR1_SQ1_Pos);  //prima temp, poi tensione
	ADC3->SQR1|=(0<<ADC_SQR1_L_Pos); //riattivalo per abilitare doppia musura
	//ADC3->PCSEL|=ADC_PCSEL_PCSEL_19|ADC_PCSEL_PCSEL_0;
	ADC3->CR&=~ADC_CR_ADCALDIF_Msk;
	ADC3->CR|=ADC_CR_ADCALLIN;
	ADC3->CR&=~ADC_CR_ADEN_Msk;
	ADC3->CR|=ADC_CR_ADCAL;
	while(ADC3->CR & ADC_CR_ADCAL) {
	}
	ADC3->ISR|=ADC_ISR_ADRDY;
	ADC3->CR|=ADC_CR_ADEN;
	while(~ADC3->ISR & ADC_ISR_ADRDY){
	}
	ADC3->ISR|=ADC_ISR_ADRDY;
	//ADC3->IER|=ADC_IER_EOCIE;
	//ADC3->SMPR2|=(7<<ADC_SMPR2_SMP_Pos);     //tempo aspettato per la temperatura
	//ADC3_COMMON->CCR|=ADC_CCR_TSEN;
	//ADC3_COMMON->CCR|=ADC_CCR_VREFEN;
}



/*uint32_t Temp_calc(uint16_t dato){       //inutile
	double TS_dif= 1.0/(TCAL_2C-TCAL_1C);
	uint32_t Cost1= 80000;
	uint32_t TEMP = (Cost1*(dato-TCAL_1C)*TS_dif)+30000;
    return TEMP;
}*/

uint32_t Volt_calc(uint16_t dato){      //al momento non la uso
	uint32_t Cost1= 3.3*1000*1000;
	uint32_t VOLT = (Cost1/dato)*VCAL_C;
    return VOLT;
}


/*void ADC_interrupt(void){
  if(MISURA<2*lun){
	  DATA=ADC3->DR;
	  if(~MISURA%2) {
		  DATAA_T[n]=DATA;
		  n++;
		  MISURA++;
	  }
	  else{
		  DATAA_V[i]=Volt_calc(DATA);
		  i++;
		  MISURA++;
	  }
  }else{
	  ADC3->ISR=ADC_ISR_EOC;
	  TIM6->CR1&=~TIM_CR1_CEN_Msk;
  }
}*/


void ADC_interrupt(void){
  if(MISURA<lun) {
	  	  DATA=ADC3->DR;
		  DATAA_T[i]=DATA;
		  i++;
		  MISURA++;
  }else{
	  USART3->TDR=((char*)DATAA_T)[0];
	  ADC3->ISR=ADC_ISR_EOC;
	  TIM6->CR1&=~TIM_CR1_CEN_Msk;
	  i=0;
	  MISURA=0;
  }
}




