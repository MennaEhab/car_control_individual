/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

#include "interrupt.h"
#include "timers.h"
#include "registers.h"

#define  INT2_EN_GPIO GICR 
#define  INT2_EN_BIT BIT5

#define  INT2_EDGE_GPIO MCUCSR
#define  INT2_EDGE_BIT BIT6

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

typedef enum EN_SwICU_Edge_t{
	SwICU_EdgeFalling ,
	SwICU_EdgeRisiging 
}EN_SwICU_Edge_t;
//int timer and interrupt
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge);
//EN_SwICU_Edge_t SwICU_GetCfgEdge(void);

//change triger

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge);

//read th TCNT

void SwICU_Read(volatile uint8_t * a_pu8_capt);

//stop timer

void SwICU_Stop(void);
void SwICU_Start(void);
/*
void SwICU_Enable(void);
void SwICU_Disable(void);
*/
#endif /* SWICU_H_ */
