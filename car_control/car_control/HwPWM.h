/*
 * HwPWM.h
 *
 *  Created on: Oct 28, 2019
 *      Author: Think
 */

#ifndef HWPWM_H_
#define HWPWM_H_

#include "timers.h"

extern void HwPWMInit(void);

extern void HwPWMSetDuty(uint8_t a_u8_duty, uint32_t a_u32_frequency);
#endif /* HWPWM_H_ */
