/*
* gpio.c
*
* Created: 1/17/2020 2:26:19 PM
*  Author: MENA
*/
#include "gpio.h"
#include "std_types.h"

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction);
void gpioPortWrite(uint8_t u8_port, uint8_t u8_value);
void gpioPortToggle(uint8_t u8_port);
uint8_t gpioPortRead(uint8_t u8_port);
void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction);
void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value);
void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins);
uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin);



void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	switch(u8_port) 
	{
		case GPIOA : PORTA_DIR = u8_direction ;
				break;
		case GPIOB : PORTB_DIR = u8_direction ;
				break;
		case GPIOC : PORTC_DIR = u8_direction ;
				break;
		case GPIOD : PORTD_DIR = u8_direction ;
				break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	switch(u8_port)
	{
		case GPIOA : PORTA_DATA = u8_value ;
			break;
		case GPIOB : PORTB_DATA = u8_value ;
			break;
		case GPIOC : PORTC_DATA = u8_value ;
			break;
		case GPIOD : PORTD_DATA = u8_value ;
			break;
	}
}


void gpioPortToggle(uint8_t u8_port)
{
	switch(u8_port)
	{
		case GPIOA : PORTA_DATA = PORTA_DATA ^ (HIGH) ;
			break;
		case GPIOB : PORTB_DATA = PORTB_DATA ^ (HIGH) ;
			break;
		case GPIOC : PORTC_DATA = PORTC_DATA ^ (HIGH) ;
			break;
		case GPIOD : PORTD_DATA = PORTD_DATA ^ (HIGH) ;
			break;
	}
}

 

uint8_t gpioPortRead(uint8_t u8_port)
{
	switch(u8_port)
	{
		case GPIOA : return PORTA_PIN ;
			break;
		case GPIOB : return PORTB_PIN ;
			break;
		case GPIOC : return PORTC_PIN ;
			break;
		case GPIOD : return PORTD_PIN ;
			break;
	}
}


void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	
	// HIGH -> output .. OR
	if (u8_direction == HIGH ){
	switch(u8_port)
	{
		case GPIOA : 
		
		PORTA_DIR = PORTA_DIR | u8_pins ;
			break;
			
		case GPIOB : 
		 
		PORTB_DIR = PORTB_DIR | u8_pins ;
			break;
			
		case GPIOC : 
				 
		PORTC_DIR = PORTC_DIR | u8_pins ;
			break;

		case GPIOD : 
				 
		PORTD_DIR = PORTD_DIR | u8_pins ;
			break;

	}
	}else {
		switch(u8_port) {
		case GPIOA :
		
		PORTA_DIR = PORTA_DIR & ~(u8_pins) ;
		break;
		
		case GPIOB :
		
		PORTB_DIR = PORTB_DIR & ~(u8_pins) ;
		break;
		
		case GPIOC :
		
		PORTC_DIR = PORTC_DIR & ~(u8_pins) ;
		break;

		case GPIOD :
		
		PORTD_DIR = PORTD_DIR & ~(u8_pins) ;
		break;		 
		
		}
	}
	
}


void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	 /*if (u8_value == HIGH ){
		switch(u8_port)
		{
			case GPIOA :
			
			PORTA_DATA  |=  u8_pins ;
			break;
			
			case GPIOB :
			
			PORTB_DATA | = u8_pins ;
			break;
			
			case GPIOC :
			
			PORTC_DATA | = u8_pins ;
			break;

			case GPIOD :
			
			PORTD_DATA | =  u8_pins ;
			break;

		}
		}else {
		
		case GPIOA :
		
		PORTA_DATA & = ~(u8_pins) ;
		break;
		
		case GPIOB :
		
		PORTB_DATA & =  ~(u8_pins) ;
		break;
		
		case GPIOC :
		
		PORTC_DATA & = ~(u8_pins) ;
		break;

		case GPIOD :
		
		PORTD_DATA & = ~(u8_pins) ;
		break;
		
	} */
	  
	 uint8_t temp ;
	 switch (u8_port) {
	 case GPIOA : 
	 temp =  PORTA_DATA  & ~(u8_pins) ;
	 PORTA_DATA = temp |(u8_value&u8_pins) ;
	 break;
	 case GPIOB : 
	 temp =  PORTB_DATA  & ~(u8_pins) ;
	 PORTB_DATA = temp |(u8_value&u8_pins) ;
	 break;
	 case GPIOC :
	 temp =  PORTC_DATA  & ~(u8_pins) ;
	 PORTC_DATA = temp |(u8_value&u8_pins) ;
	 break;
	 case GPIOD :
	 temp =  PORTD_DATA  & ~(u8_pins) ;
	 PORTD_DATA = temp |(u8_value&u8_pins) ;
	 break;}

}


void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins) 
{
	switch(u8_port)
	{
		case GPIOA : PORTA_DATA ^= (u8_pins) ;
		break;
		case GPIOB : PORTB_DATA ^= (u8_pins) ;
		break;
		case GPIOC : PORTC_DATA ^= (u8_pins) ;
		break;
		case GPIOD : PORTD_DATA ^= (u8_pins) ;
		break;
	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
	switch(u8_port)
	{
		case GPIOA : return PORTA_PIN &  (u8_pin) ;
		break;
		case GPIOB : return (PORTB_PIN &  (u8_pin)) ;
		break;
		case GPIOC : return PORTC_PIN &  (u8_pin) ;
		break;
		case GPIOD : return PORTD_PIN &  (u8_pin) ;
		break;
	}
	
}