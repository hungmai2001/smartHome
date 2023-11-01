#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"
#include "drivers/led.h"
#include "drivers/switches.h"
#include "driverlib/interrupt.h"
#include <string.h>
#include "inc/hw_gpio.h"
#include "inc/tm4c123ge6pm.h"
#include "inc/hw_nvic.h"

#define LIGHT 1
#define FAN 2
#define DOOR 3
#define SENSOR 4

//set time for init sensor : 10s
#define TIME_SENSOR 20
//set time for horn: 30s
#define TIME_HORN   30

void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    while(1)
    {
    }
}

void
ConfigureUART(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);
}

static void receiveToControlTask(void *pvParameters);
static void buttonLightTask(void *pvParameters);
static void buttonFanTask(void *pvParameters);
static void buttonSensorTask(void *pvParameters);
void vApplicationTickHook( void );
void getValueSensorTask(void *pvParameters);
void UARTIntHandler(void);
static void pTimerCallback( xTimerHandle xTimer );
xTimerHandle    myTimer;

char str[40];
uint8_t timeSensor = 0;
uint8_t timeHorn = 0;
uint8_t i = 0;
uint8_t stateLight = 0;
uint8_t stateFan = 0;
uint8_t stateDoor = 0;
uint8_t stateSensor = 0;
xQueueHandle xQueue;

/* Define the structure type that will be passed on the queue. */
typedef struct
{
    uint8_t device;
    uint8_t state;
} Data_t;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART1); //enable the UART interrupt
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
    ledInit();
    //ConfigureUART();
    switchInit();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0C);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5|GPIO_PIN_6, 0);

    xQueue = xQueueCreate( 6, sizeof(Data_t));
    myTimer = xTimerCreate(((const signed char *)"cooler Timer"),
                                    (1000),
                                    pdTRUE,
                                    (void *)(0),
                                    pTimerCallback);

    (xTimerStart(myTimer,1000) );

    xTaskCreate( buttonLightTask, "button light", 1000, NULL, 1, NULL );
    xTaskCreate( buttonFanTask, "button fan", 1000, NULL, 1, NULL );
    xTaskCreate( buttonSensorTask, "button sensor", 1000, NULL, 1, NULL );
    xTaskCreate( getValueSensorTask, "get value sensor", 1000, NULL, 1, NULL );
    xTaskCreate( receiveToControlTask, "control home", 1000, NULL, 2, NULL );
    vTaskStartScheduler();
    while(1)
    {
    }
}

void UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true); //get interrupt status
    UARTIntClear(UART1_BASE, ui32Status); //clear the asserted interrupts
    i=0;
    Data_t data;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    while(UARTCharsAvail(UART1_BASE)) //loop while there are chars
    {
        str[i] = UARTCharGetNonBlocking(UART1_BASE);
        SysCtlDelay(SysCtlClockGet() / (1000 * 3));
        i++;
    }
    if(strcmp(str, "Mở đèn" ) == 0){
        data.device = 1;
        data.state = 1;
        xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "Tắt Đèn" ) == 0){
        data.device = 1;
        data.state = 0;
        xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "mở quạt" ) == 0){
        data.device = 2;
        data.state = 1;
        xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "tắt quạt" ) == 0){
           data.device = 2;
           data.state = 0;
           xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "mở cửa" ) == 0){
            data.device = 3;
            data.state = 1;
            xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "đóng cửa" ) == 0){
            data.device = 3;
            data.state = 0;
            xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "Bật báo trộm" ) == 0){
            data.device = 4;
            data.state = 1;
            xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    else if(strcmp(str, "tắt báo trộm" ) == 0){
            data.device = 4;
            data.state = 0;
            xQueueSendFromISR( xQueue, &data, &xHigherPriorityTaskWoken );
    }
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    int m;
    for(m=0;m<40;m++)
        str[m] = 0;
}

void receiveToControlTask(void *pvParameters){
    Data_t data;
    portBASE_TYPE xStatus;
    while(1){
        xStatus = xQueueReceive( xQueue, &data, portMAX_DELAY );
        if( xStatus == pdPASS ){
            if(data.device == 1){
                if(data.state == 0){
                    ledControl(LEDRED,OFF);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0<<1);
                    stateLight = 0;
                }
                else if(data.state == 1){
                    ledControl(LEDRED,ON);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 1<<1);
                    stateLight = 1;
                }
                else{
                    if(stateLight == 1){
                        ledControl(LEDRED,OFF);
                        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0<<1);
                        stateLight = 0;
                    }
                    else{
                        ledControl(LEDRED,ON);
                        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 1<<1);
                        stateLight = 1;
                    }
                }
            }
            if(data.device == 2){
                if(data.state == 0){
                    ledControl(LEDBLUE,OFF);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 1<<2);
                    stateFan = 0;
                }
                else if(data.state == 1){
                    ledControl(LEDBLUE,ON);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0<<2);
                    stateFan = 1;
                }
                else{
                    if(stateFan == 1){
                        ledControl(LEDBLUE,OFF);
                        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 1<<2);
                        stateFan = 0;
                    }
                    else{
                        ledControl(LEDBLUE,ON);
                        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0<<2);
                        stateFan = 1;
                    }
                }
            }
            if(data.device == 3){
                if(data.state == 0){
                    ledControl(LEDGREEN,OFF);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 1<<3);
                    stateDoor = 0;
                }
                else{
                    ledControl(LEDGREEN,ON);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0<<3);
                    stateDoor = 1;
                }
            }
            if(data.device == 4){
                if(data.state == 0){
                    ledControl(LEDBLUE,OFF);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0<<5);
                    stateSensor = 0;
                }
                else if(data.state == 1){
                    ledControl(LEDBLUE,ON);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 1<<5);
                    stateSensor = 1;
                }
                else{
                    if(stateSensor == 1){
                        ledControl(LEDBLUE,OFF);
                        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0<<5);
                        stateSensor = 0;
                    }
                    else{
                        ledControl(LEDBLUE,ON);
                        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 1<<5);
                        stateSensor = 1;
                    }
                }
            }

        }
    }
}
void buttonLightTask(void *pvParameters){
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    Data_t  data;
    while(1){
        while(switchState(1)==PRESSED){
                data.device = 1;
                data.state = 2;
                xStatus = xQueueSend( xQueue, &data, xTicksToWait );
                while(switchState(1)== PRESSED);
        }
    }
}
void buttonFanTask(void *pvParameters){
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    Data_t  data;
    while(1){
        while(switchState(2)==PRESSED){
                data.device = 2;
                data.state = 2;
                xStatus = xQueueSend( xQueue, &data, xTicksToWait );
                while(switchState(2)== PRESSED);
        }
    }
}
void buttonSensorTask(void *pvParameters){
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    Data_t  data;
    while(1){
        while(switchState(3)==PRESSED){
            data.device = 4;
            data.state = 2;
            xStatus = xQueueSend( xQueue, &data, xTicksToWait );
            while(switchState(3)== PRESSED);
        }
    }
}

void getValueSensorTask(void *pvParameters){
//    portBASE_TYPE xStatus;
//    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
//    Data_t  data;
    while(1){
        if(stateSensor==1){
            if(timeSensor >=TIME_SENSOR){
                ledControl(LEDRED,ON);
                while(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7)!=0){ //sensor get value 1
                    timeHorn = 1;
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 1<<6);
                    ledControl(LEDALL,OFF);
                }
                if((timeHorn < TIME_HORN)&&(timeHorn != 0)){
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 1<<6);
                    ledControl(LEDALL,OFF);
                }
                else{
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0<<6);
                    ledControl(LEDBLUE,ON);
                    timeHorn = 0;
                }
            }
            else ledControl(LEDALL,ON);
        }
        else{
            timeHorn = 0;
            timeSensor = 0;
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0<<6);
        }
    }
}
static void pTimerCallback( xTimerHandle xTimer )
{
    if(timeSensor>=20) timeSensor = 20;
    else timeSensor++;
    if(timeHorn > 0) timeHorn++;
}
