/*
 * ledRedStateMachine.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */

#ifndef LEDGREENSTATEMACHINE_H_
#define LEDGREENSTATEMACHINE_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "drivers/switches.h"
#include "drivers/led.h"
#include "uartstdio.h"
#include "debug.h"
extern uint32_t    ledGTimer;

void ledGreenStateMachineUpdate(void);

#endif /* LEDGREENSTATEMACHINE_H_ */
