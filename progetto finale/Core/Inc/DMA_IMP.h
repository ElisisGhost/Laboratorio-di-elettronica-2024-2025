/*
 * DMA_IMP.h
 *
 *  Created on: Oct 31, 2024
 *      Author: pc
 */

#ifndef INC_DMA_IMP_H_
#define INC_DMA_IMP_H_

#include <stdint.h>

#define lun 200
#define aggiunta 150   /*max 150 se no si rompe tutto */
#define trigger1 ((0.17*pow(2,16))/3.3)
#define trigger2 ((0.19*pow(2,16))/3.3)
#define post 180
void inizializzo_DMA();
void inizializzo_ADC();
void inizializzo_USART();
void interrupt_ADC_DMA();
void interrupt_USART_DMA();
void interrupt_USART();
void interrupt_ADC();


extern uint16_t dati;
extern volatile uint16_t datiADCDMA[(lun+1)*aggiunta];
extern volatile int state;
extern volatile int statee;
extern volatile int MISURA;
extern volatile int stop;
extern volatile int lost;
extern volatile int uno;
extern volatile int counter;
extern volatile int rou;










#endif /* INC_DMA_IMP_H_ */
