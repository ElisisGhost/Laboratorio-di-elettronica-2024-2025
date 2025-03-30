/*
 * DMA_IMP.c
 *
 *  Created on: Oct 31, 2024
 *      Author: pc
 */

#include "usart.h"
#include "DMA_IMP.h"
#include <stdint.h>
#include "adc.h"

uint16_t dati;
volatile uint16_t datiADCDMA[(lun + 1)*aggiunta];
volatile int state = 0;
volatile int statee = 0;
volatile int MISURA = 0;
volatile int rou = 0;
volatile int stop;
volatile int lost;
volatile int uno;
volatile int counter;

void inizializzo_DMA(void) {
	DMA2_Stream0->M0AR = (uint32_t) &datiADCDMA;
	DMA1_Stream3->M0AR = (uint32_t) &datiADCDMA;
	DMA2_Stream0->PAR = (uint32_t) &ADC3->DR;
	DMA1_Stream3->PAR = (uint32_t) &USART3->TDR;
	DMA2->LIFCR = 0xffffffff;
	DMA2->HIFCR = 0xffffffff;
	DMA1->LIFCR = 0xffffffff;
	DMA1->HIFCR = 0xffffffff;
	DMA1_Stream3->CR |= DMA_SxCR_TCIE;
	//DMA2_Stream0->CR|=DMA_SxCR_TCIE;
	DMA2_Stream0->CR |= DMA_SxCR_CIRC;

}
void inizializzo_USART(void) {

	USART3->CR1 |= USART_CR1_RE;
	USART3->CR1 |= USART_CR1_TE;
	USART3->CR1 |= USART_CR1_UE;
	USART3->ICR |= USART_ICR_ORECF;
	USART3->ICR |= USART_ICR_TCCF;
	USART3->RQR |= USART_RQR_RXFRQ;
	USART3->CR1 |= USART_CR1_RXNEIE;

}

void interrupt_USART_DMA(void) {

		DMA1->LIFCR = 0xffffffff;
		DMA1->HIFCR = 0xffffffff;
		DMA1_Stream3->CR &= ~DMA_SxCR_EN_Msk;
/*		for(int i=0; i<1005; i++){
			datiADCDMA[i]=0;
		}*/
		//prova a far partire più vettori contemporaneamente gfyu

}

void inizializzo_ADC(void) {
	ADC3->SQR1 = 0;
	ADC3->SQR1 |= (0 << ADC_SQR1_SQ1_Pos);
	ADC3->SQR1 |= (0 << ADC_SQR1_L_Pos);
	ADC3->CR &= ~ADC_CR_ADCALDIF_Msk;
	ADC3->CR |= ADC_CR_ADCALLIN;
	ADC3->CR &= ~ADC_CR_ADEN_Msk;
	ADC3->CR |= ADC_CR_ADCAL;
	while (ADC3->CR & ADC_CR_ADCAL) {
	}
	ADC3->ISR |= ADC_ISR_ADRDY;
	ADC3->CR |= ADC_CR_ADEN;
	while (~ADC3->ISR & ADC_ISR_ADRDY) {
	}
	ADC3->ISR |= ADC_ISR_ADRDY;
	ADC3->IER |= ADC_IER_EOCIE;
	ADC3->CFGR |= 3 << ADC_CFGR_DMNGT_Pos;
}

void interrupt_ADC_DMA(void) {
	/*	ADC3->CR|=ADC_CR_ADSTP;
	 TIM6->CR1&=~TIM_CR1_CEN_Msk;
	 DMA2_Stream0->CR&=~DMA_SxCR_EN_Msk;
	 DMA2->LIFCR=0xffffffff;
	 DMA2->HIFCR=0xffffffff;
	 USART3->CR3|=USART_CR3_DMAT;
	 DMA1_Stream3->CR|=DMA_SxCR_EN; */
}

/*void interrupt_USART(void){
 if ( USART3->ISR & USART_ISR_RXNE_RXFNE) {
 if (USART3->RDR=='\r'){
 DMA2_Stream0->NDTR=lun;
 DMA1_Stream3->NDTR=(lun+1)*2;
 ADC3->CFGR|=(1<<ADC_CFGR_DMNGT_Pos);
 DMA2_Stream0->CR|=DMA_SxCR_EN;
 ADC3->CR|=ADC_CR_ADSTART;
 TIM6->CR1|=TIM_CR1_CEN;
 }

 } else {
 USART3->RQR |= USART_RQR_RXFRQ;
 }
 }*/

/*void interrupt_ADC(void){
 if(counter<200){
 counter++;
 ADC3->ISR|=ADC_ISR_EOC;
 }else{
 if((ADC3->DR)<trigger1){
 state=1;
 }
 if(state==1&&(ADC3->DR)>trigger2){
 MISURA++;
 statee=1;
 state=0;
 }
 if(statee==1&&MISURA<post){
 MISURA++;
 ADC3->ISR|=ADC_ISR_EOC;
 }
 if(MISURA==post){
 //stop
 TIM6->CR1&=~TIM_CR1_CEN_Msk;
 stop=lun-(DMA2_Stream0->NDTR);
 statee=0;
 MISURA=0;
 counter=0;
 datiADCDMA[lun]=stop;
 USART3->CR3|=USART_CR3_DMAT;
 DMA1_Stream3->CR|=DMA_SxCR_EN;
 ADC3->ISR|=ADC_ISR_EOC;
 }
 }
 }*/
