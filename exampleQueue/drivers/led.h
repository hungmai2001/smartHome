#ifndef LED_H_
#define LED_H_
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define RED 2
#define BLUE 4
#define GREEN 8

enum ledChoose {LEDRED, LEDGREEN, LEDBLUE, LEDALL} led;
enum ledState {OFF,ON} stateLed;

void ledInit(void);
void ledControl(enum ledChoose led, enum ledState stateLed);

#endif /* LED_H_ */
