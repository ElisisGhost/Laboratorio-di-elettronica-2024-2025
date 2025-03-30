/*
 * ESPE_seriale..h
 *
 *  Created on: Oct 20, 2023
 *      Author: utente
 */

// #ifndef INC_ESPE_SERIALE__H_
// #define INC_ESPE_SERIALE__H_

//extern unsigned char stringa[];
extern unsigned char risposta[];
extern uint16_t numeri[];

//#define lunghezza_stringa sizeof(stringa) /sizeof(stringa[0])
#define lunghezza_risposta 100

extern unsigned int indice;
extern unsigned int NUM;

// #endif /* INC_ESPE_SERIALE__H_ */

//Ricordiamoci che tutto quanto definito nel .c qui va ripreso con extern

void ESPE_USART_interrupt(void);
void inizializzo_USART(void);
void Bottone(void);
//void ESPONENZIALE(void);

