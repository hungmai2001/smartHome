/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */
#include "ledGreenStateMachine.h"


typedef     enum {S_LEDON=0,S_LEDONWAIT1,S_LEDONWAIT2, S_LEDOFF, S_LEDOFFWAIT1,S_LEDOFFWAIT2}  ledGState_t;
uint32_t    ledGTimer = 0;

static ledGState_t State = S_LEDOFF;

#ifdef  DEBUG
  static const  char *stateName[6]={
                            "S_LEDON",
                              "S_LEDONWAIT1",
                              "S_LEDONWAIT2",
                              "S_LEDOFF",
                              "S_LEDOFFWAIT1",
                              "S_LEDOFFWAIT2"
                             };

#endif
void ledGreenStateMachineUpdate(void)
{
    switch (State)
    {
        case S_LEDOFF:
            if (switchState(2) == PRESSED)
                {
                    State = S_LEDOFFWAIT1;
                    ledGTimer = 3000;       //set timer to 3 sec
                    DBG("State = %s\n",stateName[State]);
                }
            break;
        case S_LEDOFFWAIT1:
                    if (switchState(2) == RELEASED) //if switch is release before timer counting down to 0
                        {
                            State = S_LEDOFF;       //come back to OFF state
                            DBG("State = %s\n",stateName[State]);
                        }
                    else if (ledGTimer==0)
                    {
                        State = S_LEDOFFWAIT2;
                        DBG("State = %s\n",stateName[State]);
                    }
                    break;
        case S_LEDOFFWAIT2:
            if (switchState(2) == RELEASED)
                {
                    State = S_LEDON;
                    DBG("State = %s\n",stateName[State]);
                }
            break;
        case S_LEDON:
                    if (switchState(2) == PRESSED)
                        {
                            State = S_LEDONWAIT1;
                            ledGTimer = 6000;       //set timer to 3 sec
                            DBG("State = %s\n",stateName[State]);
                        }
                    break;
        case S_LEDONWAIT1:
                     if (switchState(2) == RELEASED) //if switch is release before timer counting down to 0
                         {
                             State = S_LEDON;       //come back to OFF state
                             DBG("State = %s\n",stateName[State]);
                         }
                     else if (ledGTimer==0)
                     {
                         State = S_LEDONWAIT2;
                         DBG("State = %s\n",stateName[State]);
                     }
                     break;
         case S_LEDONWAIT2:
             if (switchState(2) == RELEASED)
                 {
                     State = S_LEDOFF;
                     DBG("State = %s\n",stateName[State]);
                 }
             break;
    }
    switch (State)
    {
    case    S_LEDOFF:
    case    S_LEDOFFWAIT1:
    case    S_LEDONWAIT2:
        ledControl(LEDGREEN,OFF);
        break;
    case S_LEDON:
    case    S_LEDOFFWAIT2:
    case    S_LEDONWAIT1:
        ledControl(LEDGREEN,ON);
        break;
    }
}
