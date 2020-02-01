/*
 * ultrasonic.c
 *
 * Created: 1/29/2020 7:58:31 PM
 *  Author: MENA
 */ 

#include "SwICU.h"
#include "Ultrasonic.h"
#define  tickTimeUs 16

void ultrasonic_init(){
	
	uint16_t Distance ;
	//trigger
	gpioPinWrite(GPIOC , BIT0 , 1);
	
	timer2DelayMs(5);
	
	gpioPinWrite(GPIOC , BIT0 , 0);
	
	
	
	//Distance = 15 ;
	
	Distance = calculate() ;
	
	gpioPinWrite(GPIOB , BIT4|BIT5|BIT6|BIT7 , Distance<<4) ;
	
	timer2DelayMs(60);
	
	 
}

uint16_t calculate(){
	
	uint8_t * no_of_ticks ;
	uint16_t timerOfTicks_Us  ;
	uint16_t Distance ;
	SwICU_Read(no_of_ticks);
	
	timerOfTicks_Us = *no_of_ticks * tickTimeUs ;
	
	Distance = timerOfTicks_Us/58 ;
	if (Distance > 15 ){
		Distance = 15 ;
	}
	//Distance = 3 ; 
	return Distance;
	
	// microsec/58 = cm
	
	
	
} 