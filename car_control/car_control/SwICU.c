/*
 * CFile1.c
 *
 * Created: 1/29/2020 2:44:47 PM
 *  Author: MENA
 */ 

#include "SwICU.h"
#include "timers.h"
#include "led.h"
#include "avr/interrupt.h"
//int timer and interrupt

static volatile EN_SwICU_Edge_t flag = SwICU_EdgeRisiging ;

static uint16_t TCNT_value = 0 ;



ISR(INT2_vect){
	//Led_Init(LED_1);
	//Led_On(LED_1);
	switch (flag){
		
		case SwICU_EdgeRisiging :
		
		SwICU_Start();
		MCUCSR &= ~(1<<6) ;
		//Led_On(LED_0) ;
		flag = SwICU_EdgeFalling;
		break;
		
		case SwICU_EdgeFalling :
		
		SwICU_Stop();
		MCUCSR |= 1<<6 ;
		//Led_Off(LED_0) ;
		flag = SwICU_EdgeRisiging;
		break;
		
	}
	
	
}

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	
	timer0Init(T0_NORMAL_MODE ,T0_OC0_SET, T0_PRESCALER_256, 0 , 0,T0_POLLING) ;
	
	// interrupt initialization
	if(a_en_inputCaptureEdge == SwICU_EdgeRisiging){
		
		
		MCUCSR |= 1<<6 ;
		//
		//Led_Init(LED_2);
		//Led_On(LED_2) ;
		}
	else 
		
		MCUCSR &= ~(1<<6) ;
		
	GICR |= 1<<5;
	
}

//EN_SwICU_Edge_t SwICU_GetCfgEdge(void);

//change triger

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge){
	
	if(a_en_inputCaptureEdgeedge== SwICU_EdgeRisiging)
		SET_BIT(INT2_EDGE_GPIO , INT2_EN_BIT);
	else
		CLEAR_BIT(INT2_EDGE_GPIO , INT2_EN_BIT);
}

//read th TCNT

void SwICU_Read(volatile uint8_t * a_pu8_capt){
	
	*(a_pu8_capt) = TCNT_value ;
}

//stop timer

void SwICU_Stop(void){
	timer0Stop() ;
	TCNT_value = timer0Read() ;
	TCNT0 = 0 ;
	
}

//
void SwICU_Start(void){
	timer0Start() ;
	
}
