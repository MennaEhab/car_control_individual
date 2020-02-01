/*
 * HwPWM.c
 *
 * Created: 1/30/2020 4:36:04 PM
 *  Author: MENA
 */ 
#include "HwPWM.h"

#define PWM_PRE_SCALE 64
#define PWM_PRE_scale_MASK T1_PRESCALER_1024
uint8_t global_duty = 0;
uint8_t global_req_freq = 0;

void HwPWMInit(void){
	
uint16_t ICR_TOP ;
uint16_t duty_cycle_tick ;


ICR_TOP = F_CPU / (2.0 * PWM_PRE_SCALE * global_req_freq) ;


//ICR_TOP = 0x004E;

duty_cycle_tick = ICR_TOP *global_duty/100.0 ;
timer1Init(T1_PHASE_CORRECT_ICR1, T1_OC1A_CLEAR|T1_OC1B_CLEAR , 
			PWM_PRE_scale_MASK , 0 , duty_cycle_tick, duty_cycle_tick,ICR_TOP, T1_POLLING);	
	TCCR1 |= 0x0005;
	
	//timer1Start();
}


void HwPWMSetDuty(uint8_t a_u8_duty, uint32_t a_u32_frequency){
	
	global_duty = a_u8_duty ;
	global_req_freq = a_u32_frequency ;
	HwPWMInit();
	
}