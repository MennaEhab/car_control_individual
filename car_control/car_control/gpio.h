/*
 * gpio.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"
#include "registers.h"


#define GPIOA	0
#define GPIOB	1
#define GPIOC	2
#define GPIOD	3

/************************************************************************/
/*				 Enum for defining bit numbers                          */
/************************************************************************/
typedef enum EN_bits_t
{
	BIT0 = 0x01,	// defines BIT0 in a register
	BIT1 = 0x02,	// defines BIT1 in a register
	BIT2 = 0x04,	// defines BIT2 in a register
	BIT3 = 0x08,	// defines BIT3 in a register
	BIT4 = 0x10,	// defines BIT4 in a register
	BIT5 = 0x20,	// defines BIT5 in a register
	BIT6 = 0x40,	// defines BIT6 in a register
	BIT7 = 0x80,	// defines BIT7 in a register
}EN_bits_t;

#define INPUT	(0)
#define OUTPUT	(0xFF)

/************************************************************************/
/*				 GPIO functions' prototypes	                            */
/************************************************************************/

/*===========================PORT Control===============================*/
/**
 * Description: set port direction (which is DDR register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction: set the port direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
extern void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction);

/**
* Description: set the port value (which is PORT register)
* @param port: portID and takes the following values
* 				- 0 -> GPIOA
* 				- 1 -> GPIOB
* 				- 2 -> GPIOC
* 				- 3 -> GPIOD
* @param value: set the port value and takes the following values
* 				- 0x00 -> Low
* 				- 0xff -> High
*/

extern void gpioPortWrite(uint8_t u8_port, uint8_t u8_value);

/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
extern void gpioPortToggle(uint8_t u8_port);

/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
extern uint8_t gpioPortRead(uint8_t u8_port);

/*===========================PIN Control===============================*/
/**
 * Description: set selected pins (more than one pin [ORed]) direction
 *
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to set its direction and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 *
 * @param direction: set the pins direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
extern void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction);

/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
extern void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value);

/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 */
extern void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins);

/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return
 */
extern uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin);



#endif /* GPIO_H_ */