#include "switches.h"


void switchInit(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //open the lock and select bits we want to modify
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //unlock PF0
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 |GPIO_PIN_0 );
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4 );
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

sw_t switchState(int swChoose){
    if(swChoose==1){
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0) return PRESSED;
        else return RELEASED;
    }
    else if(swChoose==2){
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==0) return PRESSED;
        else return RELEASED;
    }
    else if(swChoose==3){
            if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4)==0) return PRESSED;
            else return RELEASED;
        }
}
