/*
 * IncFile1.h
 *
 * Created: 1/25/2020 10:53:55 AM
 *  Author: MENA
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))



typedef enum car_direction {
	FORWARD ,
	BACKWORD
	
	
}DIRECTION;

void control (DIRECTION myDirection);
void control_init(void);
void stop(void);




#endif /* INCFILE1_H_ */