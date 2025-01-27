/*
 * car_control.c
 *
 * Created: 1/24/2020 8:07:20 PM
 * Author : MENA
 */ 

//#include <avr/io.h>

#include "dcMotor.h"

#include "led.h"
#include "gpio.h"
#include "SwICU.h"
#include "Ultrasonic.h"




int main(void)
{
	uint16_t Distance ;
	//////////// icu ////////////////////
	
	///// enable global interrupt 
	SREG |=0x80;
		/////external interrupt1 pin 
	gpioPinDirection(GPIOB , BIT2 , INPUT );
	
	///for protus 
	gpioPinWrite(GPIOB,BIT2,HIGH);
	
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	
	
	SwICU_Init(SwICU_EdgeRisiging);
	
	/// direction of trigger
	
	gpioPinDirection(GPIOC , BIT0 ,OUTPUT);
	
	timer2DelayMs(20);
	
	//////////motor///////////////
	
	/// set direction
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	
	MotorDC_Dir(MOT_1,FORWARD);
	MotorDC_Dir(MOT_2,FORWARD);
	
	/// set speed 
	
	MotorDC_Speed_HwPWM(50) ;
    
    while (1) 
    {
		// read the distance between the car and any obstacle infront of it 
		
		Distance = ultrasonic_init ();
		
		/// if the distance between the object and the car less than 5 cm the car stops 
		
		if( Distance<= 5 ){
			
			MotorDC_Dir(MOT_1,STOP);
			MotorDC_Dir(MOT_2,STOP);
		}else {
			MotorDC_Dir(MOT_1,FORWARD);
			MotorDC_Dir(MOT_2,FORWARD);
			
		}
		
		
    }
}

