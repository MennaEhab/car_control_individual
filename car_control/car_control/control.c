/*
 * control.c
 *
 * Created: 1/25/2020 10:55:07 AM
 *  Author: MENA
 */ 

#include "control.h"
#include "registers.h"
#include "std_types.h"
#include "gpio.h"

void control_init(void){
	
	gpioPinDirection(control_GPIO , BIT2|BIT3|BIT4|BIT5|BIT6|BIT7,OUTPUT);
	
}


void stop(){
	
	gpioPinWrite(control_GPIO , Enable_M1 ,LOW);
	//gpioPinWrite(control_GPIO , M1_A,LOW);
	//gpioPinWrite(control_GPIO , M1_B,LOW);
	
	gpioPinWrite(control_GPIO , Enable_M1 ,LOW);
	//gpioPinWrite(control_GPIO , M2_A,LOW);
	//gpioPinWrite(control_GPIO , M2_B,LOW);
	
}
void control (DIRECTION myDirection){
	
	switch (myDirection){
		case FORWARD :
		// enable motor 1 & 2 and set values by 0 1
		
		gpioPinWrite(control_GPIO , Enable_M1 ,HIGH);
		gpioPinWrite(control_GPIO , M1_A,LOW);
		gpioPinWrite(control_GPIO , M1_B,HIGH);
		
		gpioPinWrite(control_GPIO , Enable_M1 ,HIGH);
		gpioPinWrite(control_GPIO , M2_A,LOW);
		gpioPinWrite(control_GPIO , M2_B,HIGH);
		
		break;
		
		case BACKWORD :
		// enable motor 1 & 2 and set values by 1 0
		
		gpioPinWrite(control_GPIO , Enable_M1 ,HIGH);
		gpioPinWrite(control_GPIO , M1_A,HIGH);
		gpioPinWrite(control_GPIO , M1_B,LOW);
		
		
		gpioPinWrite(control_GPIO , Enable_M1 ,HIGH);
		gpioPinWrite(control_GPIO , M2_A,HIGH);
		gpioPinWrite(control_GPIO , M2_B,LOW);
		break;
		
	}
	
}