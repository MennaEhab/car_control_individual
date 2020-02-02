/*
 * Ultrasonic.h
 *
 * Created: 1/29/2020 8:12:44 PM
 *  Author: MENA
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

// function  : read the width of the echo pulse and calculate the distance 

extern uint16_t calculate(void) ;

// function : set the trigger pulse 
extern uint16_t ultrasonic_init(void);

#endif /* ULTRASONIC_H_ */