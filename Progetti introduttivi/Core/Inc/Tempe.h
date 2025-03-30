/*
 * Tempe.h
 *
 *  Created on: Oct 17, 2024
 *      Author: pc
 */

#ifndef SRC_TEMPE_H_
#define SRC_TEMPE_H_

extern uint32_t DATAA_T[];
extern uint32_t DATAA_V;
extern unsigned int MISURA;
void inizializzo_ADC(void);
uint32_t Temp_calc(uint16_t);
void ADC_interrupt(void);
void MIS_VOLT(void);














#endif /* SRC_TEMPE_H_ */
