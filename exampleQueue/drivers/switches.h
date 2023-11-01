
#ifndef SWITCHES_H_
#define SWITCHES_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

typedef enum {PRESSED,RELEASED} sw_t;
void switchInit(void);

sw_t switchState(int swChoose);
#endif /* SWITCHES_H_ */
