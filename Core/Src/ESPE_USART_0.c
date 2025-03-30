/*
 * ESPE_seriale.c
 *
 *  Created on: Oct 20, 2023
 *      Author: utente
 */
//Zona include
#include "usart.h"
#include "ESPE_USART_0.h"
#include <stdint.h>
#include "adc.h"
#include "Tempe.h"

/*#define tau1 -1.0
#define tau2 15.0
#define tau3 10.0 */
/*#define costante_1   (uint16_t)((exp(tau1/tau2))*(1<<10) )
#define costante_2  (uint16_t)((exp(tau1/tau3))*(1<<10) )*/
#define lun 100

//unsigned char stringa[] = { "Buongiorno!\r\n" };
unsigned int indice = 1;
unsigned char risposta[100];
unsigned int NUM = 0;
uint16_t numeri[lun];
//uint16_t Exp1[lun];
//uint16_t Exp2[lun];

//Zona definizione variabili, vettori globali

void inizializzo_USART(void) {

	//Accendo la trasmissione
	USART3->CR1 |= USART_CR1_RE;
	USART3->CR1 |= USART_CR1_TE;
	USART3->CR1 |= USART_CR1_UE;
	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
	USART3->CR1 |= USART_CR1_TCIE;
	USART3->CR1 |= USART_CR1_RXNEIE;
	//Abilito interrupt trasmissione: attenzione che il flag viene subito impostato ad 1

//Abilito interruput ricezione

//Accendo USART

}
//Zona definizione di funzioni

/*void ESPONENZIALE(void){
	Exp1[0]=65000;
	Exp2[0]=65000;
    numeri[0]=0;
	for(int ii=1; ii<lun; ii++) {

		Exp1[ii]=( (uint32_t)Exp1[ii-1]*(uint32_t)costante_1 ) >>10;
		Exp2[ii]=( (uint32_t)Exp2[ii-1]*(uint32_t)costante_2 ) >>10;
        numeri[ii]= Exp1[ii]-Exp2[ii];
	}
}*/


void Bottone(void) {
	ADC3->CR|=ADC_CR_ADSTART;
}

void ESPE_USART_interrupt(void) {

	 if ( USART3->ISR & USART_ISR_TC) {
		//Qui mettiamo il codice per la gestione della sola trasmissione
		 //if (indice < lunghezza_stringa) {
			//USART3->TDR = stringa[indice];
			//indice++; }
		 if (indice<lun*sizeof(uint32_t)){
				 USART3->TDR = ((char*)DATAA_T)[indice];
				 indice++;
		 } else {
			//spengo l'interrupt
			USART3->ICR |= USART_ICR_TCCF;
			indice=1;
		}
	}
	if ( USART3->ISR & USART_ISR_RXNE_RXFNE) {
		//Qui mettiamo il codice per la gestione della sola ricezione
		//crea una variabile e assegnala al registro rdr
		if (NUM < lunghezza_risposta) {
			risposta[NUM] = USART3->RDR;
			//USART3->TDR=USART3->RDR;
			NUM++;
			if (risposta[NUM-1]=='\r'){
				ADC3->CR|=ADC_CR_ADSTART;
				TIM6->CR1|=TIM_CR1_CEN;

			}

		} else {
			//spengo l'interrupt
			//NUM=0;
			USART3->RQR |= USART_RQR_RXFRQ;
		}


	}

//Per ovviare a dimenticanze azzeriamo all'uscita i flag della ricezione e trasmissione in ogni caso
	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione

//Ricordiamoci di commentare la funzione introdotta dallo IDE cosi:
//
//if (0){
//	/* USER CODE END USART3_IRQn 0 */
//	HAL_UART_IRQHandler(&huart3);
//	/* USER CODE BEGIN USART3_IRQn 1 */
//}

}
