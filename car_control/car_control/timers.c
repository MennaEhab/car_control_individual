/*
 * timers.c
 *
 * Created: 1/21/2020 1:52:53 PM
 *  Author: MENA
 */ 

#include "timers.h"
//#include <avr/interrupt.h>

#include "interrupt.h"
#include "led.h"


#define F_CPU 16000000.0 

uint16_t  global_prescale ;
uint16_t global_prescale1 ;
uint16_t global_prescale2 ;
volatile uint16_t global_input_0 ;
uint16_t prescalerValue =  1;

volatile uint8_t duty_high ;
volatile uint8_t duty_low ;
volatile duty_state myduty_state ;
volatile uint8_t global_T0frequency ;
volatile uint8_t global_T2frequency ;



void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal,
				 uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
				 {
					 
					
				 TCCR0 =  0 ;
					 TCCR0 = en_mode | en_OC0 ; 
					 //TCNT0 = u8_initialValue ;
					 timer0Set(u8_initialValue) ;
					 OCR0 = u8_outputCompare ;
					 TIMSK |= en_interruptMask ;
					 
					 global_prescale = en_prescal ;
					 
				 }


void timer0Set(uint8_t u8_value) 
		{
			TCNT0 = u8_value ;
		}		
						
uint8_t timer0Read(void){
	
		return TCNT0 ;
	
}
		
void timer0Start(void)
		{
			TCCR0 |= global_prescale ; 
		}

void timer0Stop(void)
		{
			TCCR0 &= T0_NO_CLOCK ;
		}
		
void timer0DelayMs(uint16_t u16_delay_in_ms){
	
	timer0Init(T0_COMP_MODE,T0_OC0_CLEAR,T0_PRESCALER_64, 0 , 250 ,T0_POLLING) ;
	
	TCNT0 = 12;
	// no of ticks for one milli sec 
	
	timer0Start();
	while (u16_delay_in_ms)
	{
		if(TIFR&0x02)
		{
			u16_delay_in_ms -- ;
			TCNT0 = 0 ;	
			TIFR |=0x02 ;
		}
		
	}
	timer0Stop();

}

void timer0DelayMs2(uint16_t u16_delay_in_ms){
	
	global_input_0 = u16_delay_in_ms ;

	timer0Init(T0_COMP_MODE,T0_OC0_SET,T0_PRESCALER_64, 0 , 250 ,T0_INTERRUPT_CMP) ;
	
	sei();
	TCNT0 =10;
	timer0Start();
	
	while(1)
	{
		if (global_input_0<=0)
		{
			timer0Stop();
			break;
		}
		
	}
	
}



void timer0SwPWM_new(uint8_t u8_dutyCycle,Freq u8_frequency){
	
	gpioPinDirection(T0_PWM_GPIO , T0_PWM_BIT , OUTPUT);
	//timer0Init(T0_NORMAL_MODE, T0_OC0_CLEAR, T0_PRESCALER_64 , 0 , 0, T0_INTERRUPT_ALL);
	global_T0frequency =u8_frequency ;
	switch (u8_frequency){
		
		case freq1k :
		timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_64 , 0 , 0, T0_INTERRUPT_ALL);

		duty_high = (250 * (float)(u8_dutyCycle/100.0)) ;
		duty_low = 250 - duty_high ;
		TCNT0=5;
		OCR0 = duty_low + 5;
		if (u8_dutyCycle == 100)
		{
			OCR0 = duty_low + 5+1;
		}
		//OCR0 = u8_dutyCycle ;
		
		break;
		
		case freq2k:
		
		
		timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_64 , 0 , 0, T0_INTERRUPT_ALL);

		//TCCR0 |= T0_pr
		duty_high = (float)125 * (float)(u8_dutyCycle/100.0) ;
		duty_low = 125 - duty_high  ;
		TCNT0=131;
		OCR0 = duty_low + 131;
		if (u8_dutyCycle == 100)
		{
			OCR0 = duty_low + 131+1;
		}
		break;
		
		case  freq500: timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256 , 0 , 0, T0_INTERRUPT_ALL);

		//TCCR0 |= T0_pr
		duty_high = (float)125 * (float)(u8_dutyCycle/100.0) ;
		duty_low = 125 - duty_high  ;
		TCNT0=131;
		OCR0 = duty_low + 131;
		if (u8_dutyCycle == 100)
		{
			OCR0 = duty_low + 131+1;
		}
	}
	
	
	sei();
	timer0Start();
	gpioPinWrite(T0_PWM_GPIO , T0_PWM_BIT , HIGH);
	
}

void timer0SwPWM_old(uint8_t u8_dutyCycle,Freq u8_frequency){
	
	
	gpioPinDirection(T0_PWM_GPIO , T0_PWM_BIT , OUTPUT);
	
	
	switch (u8_frequency){
		
		case freq1k :
		
		duty_high = (250 * (float)(u8_dutyCycle/100.0)) -2;
		duty_low = 250 - duty_high -2 ;
		
		break;
		
		case freq2k:
		duty_high = (float)125 * (float)(u8_dutyCycle/100.0) ;
		duty_low = 125 - duty_high -1 ;
		break;
	}
	duty_high =120;
	duty_low = 100;
	//duty_high = 125;
	//duty_low =125;
	
	duty_high =175;
	duty_low = 75;
	
	OCR0 = duty_low ;
	//TCNT0=0;
	sei();
	timer0Start();
	//gpioPinWrite(T0_PWM_GPIO , T0_PWM_BIT , HIGH);
	myduty_state = low ;
}

		
void timer0DelayUs(uint32_t u32_delay_in_us)
		{			
/*
				TCNT0 = 10;
				 no of ticks for one milli sec
				TCNT0 = 1;
				*/
		/*		timer0Start();
							
				while (u32_delay_in_us)
				{
					if(TIFR&0x02)
					{
						u32_delay_in_us -- ;
						TCNT0 = 0 ;
						TIFR |=0x02 ;
					}
					
				}
				timer0Stop();	*/
		global_input_0 = u32_delay_in_us;
		sei();
		timer0Init(T0_COMP_MODE, T0_OC0_CLEAR , T0_NO_CLOCK , 0, 16, T0_INTERRUPT_CMP);
		
		
		timer0Start();
		
		while(global_input_0);
		
		timer0Stop();
		
		}

ISR(TIMER0_COMP_vect){
/*	timer0Stop();
	
	switch(myduty_state){
		
		case low :
		//TCNT0 = 0;
		OCR0 = duty_high ;
		myduty_state = high;
		//TCNT0 = 0;
		gpioPinToggle( T0_PWM_GPIO , T0_PWM_BIT  );
		break;
		case high :
		//TCNT0 = 0;
		OCR0 = duty_low ;
		myduty_state = low;
		//TCNT0 = 0;
		gpioPinToggle( T0_PWM_GPIO , T0_PWM_BIT  );
		break;
	}
	timer0Start(); */

gpioPinWrite( T0_PWM_GPIO , T0_PWM_BIT , HIGH);	
}

ISR(TIMER0_OVF_vect){
	gpioPinWrite( T0_PWM_GPIO , T0_PWM_BIT ,LOW);	
	switch (global_T0frequency){
		case freq1k : TCNT0 = 5 ;
				break;
		case freq2k : TCNT0 = 131 ;
				break;
		case  freq500 : TCNT0 = 131 ;
				break;
		
	}
	
	
}

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, 
				uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,
				uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask){
					
					TCCR1 = 0 ;		
					global_prescale1 = en_prescal ;
					TCCR1 = en_mode | en_OC ;
					ICR1= u16_inputCapture ;
					timer1Set(u16_initialValue) ;
					OCR1A = u16_outputCompareA ;
					OCR1B = u16_outputCompareB ;
					TIMSK |= en_interruptMask ; 
					
				}
				
				
				
void timer1Set(uint16_t u16_value){
	TCNT1 = u16_value ;
	
}

uint16_t timer1Read(void){
	
	return TCNT1 ;
	
}

void timer1Start(void){
	
	TCCR1 |= global_prescale1 ;
	
}

void timer1Stop(void){
	
	TCCR1 = T1_NO_CLOCK ;
}

void timer1DelayMs(uint16_t u16_delay_in_ms){
	
		timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1A_CLEAR ,T1_PRESCALER_64, 0 , 250 , 0, 0 , T2_POLLING) ;
		// for the time taken by the timer Init function 
		TCNT1 = 29;
		// no of ticks for one milli sec
		timer1Start();
		while (u16_delay_in_ms)
		{
			if(TIFR&0x10)
			{
				u16_delay_in_ms -- ;
				TCNT1 = 0 ;
				TIFR |=0x10 ;
			}	
		}
		timer1Stop();
	
}

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, 
				uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, 
				En_timer2Interrupt_t en_interruptMask){
					
					ASSR &= 0xF0 ;  
					TCCR2 =  0 ;
					TCCR2 = en_mode | en_OC ;
					//TCNT0 = u8_initialValue ;
					timer2Set(u8_initialValue) ;
					OCR2 = u8_outputCompare ;
					TIMSK |= en_interruptMask ;
					
					global_prescale2 = en_prescal ;
					
					}

void timer2Set(uint8_t u8_a_value){
	
	TCNT2 = u8_a_value ;
	
}

uint8_t timer2Read(void){
	
	return TCNT2 ;
	
}

void timer2Start(void){
	
	TCCR2 |= global_prescale2 ;
}

void timer2Stop(void){
	
	TCCR0 &= T0_NO_CLOCK ;
	
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
	
	
	timer2Init(T2_COMP_MODE,T2_OC2_DIS,T2_PRESCALER_64, 0 , 250, 0,T2_POLLING) ;

	TCNT2 = 12;
	// no of ticks for one Milli-sec
	timer2Start();
	while (u16_delay_in_ms)
	{
		if(TIFR&0x80)
		{
			u16_delay_in_ms -- ;
			TCNT2 = 0 ;
			TIFR |=0x80 ;
		}
		
	}
	timer2Stop();
}

void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	
	
	
	gpioPinDirection(T2_PWM_GPIO1 , T2_PWM_BIT1 , OUTPUT);
	gpioPinDirection(T2_PWM_GPIO2 , T2_PWM_BIT2 , OUTPUT);
	
	//timer0Init(T0_NORMAL_MODE, T0_OC0_CLEAR, T0_PRESCALER_64 , 0 , 0, T0_INTERRUPT_ALL);
	global_T2frequency =u8_frequency ;
	switch (u8_frequency){
		
		case freq1k :
		timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_64 , 0 , 0,0, T2_INTERRUPT_ALL);

		duty_high = (250 * (float)(u8_dutyCycle/100.0)) ;
		duty_low = 250 - duty_high ;
		TCNT2=5;
		OCR2 = duty_low + 5;
		if (u8_dutyCycle == 100)
		{
			OCR2 = duty_low + 5+1;
		}
		//OCR0 = u8_dutyCycle ;
		
		break;
		
		case freq2k:
		
		
		timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_64 , 0 , 0,0, T2_INTERRUPT_ALL);

		//TCCR0 |= T0_pr
		duty_high = (float)125 * (float)(u8_dutyCycle/100.0) ;
		duty_low = 125 - duty_high  ;
		TCNT2=131;
		OCR2 = duty_low + 131;
		if (u8_dutyCycle == 100)
		{
			OCR2 = duty_low + 131+1;
		}
		break;
		
		case  freq500: timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_256 , 0 , 0,0, T2_INTERRUPT_ALL);

		//TCCR0 |= T0_pr
		duty_high = (float)125 * (float)(u8_dutyCycle/100.0) ;
		duty_low = 125 - duty_high  ;
		TCNT2=131;
		OCR2 = duty_low + 131;
		if (u8_dutyCycle == 100)
		{
			OCR2 = duty_low + 131+1;
		}
	}
	
	
	sei();
	timer2Start();
	gpioPinWrite(T2_PWM_GPIO1 , T2_PWM_BIT1 , HIGH);
	gpioPinWrite(T2_PWM_GPIO2 , T2_PWM_BIT2 , HIGH);
	
}

ISR(TIMER2_COMP_vect){
/*	timer0Stop();
	
	switch(myduty_state){
		
		case low :
		//TCNT0 = 0;
		OCR0 = duty_high ;
		myduty_state = high;
		//TCNT0 = 0;
		gpioPinToggle( T0_PWM_GPIO , T0_PWM_BIT  );
		break;
		case high :
		//TCNT0 = 0;
		OCR0 = duty_low ;
		myduty_state = low;
		//TCNT0 = 0;
		gpioPinToggle( T0_PWM_GPIO , T0_PWM_BIT  );
		break;
	}
	timer0Start(); */

gpioPinWrite( T2_PWM_GPIO1 , T2_PWM_BIT1 ,HIGH);
gpioPinWrite( T2_PWM_GPIO2 , T2_PWM_BIT2 ,HIGH);
}

ISR(TIMER2_OVF_vect){
	gpioPinWrite( T2_PWM_GPIO1 , T2_PWM_BIT1 ,LOW);
	gpioPinWrite( T2_PWM_GPIO2 , T2_PWM_BIT2 ,LOW);	
	switch (global_T0frequency){
		case freq1k : TCNT0 = 5 ;
				break;
		case freq2k : TCNT0 = 131 ;
				break;
		case  freq500 : TCNT0 = 131 ;
				break;
		
	}
	
	
}