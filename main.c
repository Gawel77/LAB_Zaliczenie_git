#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

void Automat(void) {
    enum LedState { STOP, LEFT, RIGHT };
    static enum LedState eLedState = STOP;

    switch (eLedState) 
		{
        case STOP:
            if (eKeyboardRead() == BUTTON_0) 
						{
                eLedState = LEFT;
            } 
						else if (eKeyboardRead() == BUTTON_2) 
						{
                eLedState = RIGHT;
            } 
						else 
						{
                eLedState = STOP;
            }
            break;

        case LEFT:
            if (eKeyboardRead() == BUTTON_1) 
						{
                eLedState = STOP;
            } 
						else 
						{
                LedStepLeft();
                eLedState = LEFT;
            }
            break;

        case RIGHT:
            if (eKeyboardRead() == BUTTON_1) 
						{
                eLedState = STOP;
            } 
						else 
						{
                LedStepRight();
                eLedState = RIGHT;
            }
            break;
    }
}

int main(void) 
{
		unsigned int iMainLoopCtr;
    LedInit();
    KeyboardInit();
    
    Timer0Interrupts_Init(20000, &Automat);

    while(1) 
		{
				iMainLoopCtr++;
    }
}

