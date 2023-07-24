#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <peekpoke.h>
//#include "c64.h"
//#include "types.h"
//#include "all.h"
//#include "items.h"
//#include "room.h"

/* input handling -- C64 Specific! */
bool NextMove() {
    unsigned char key,joy1,joy2;
    bool evalKeyboard = false;

    D=-1;
    while(D==-1) {
        //Loop till input
        key = GET_PKEY_VIEW;
        joy1 = GET_JOY1;
        joy2 = GET_JOY2;

        // Evaluate joysticks first -- joy1 interferes with the keyboard!
        if((joy1 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
            if((joy2 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) evalKeyboard = true;
        }
        else {
            if((joy1 & C64_JOYSTICK_UP) == 0) D=2;
            else if((joy1 & C64_JOYSTICK_DOWN) == 0) D=3;
            else if((joy1 & C64_JOYSTICK_LEFT) == 0) D=0;
            else if((joy1 & C64_JOYSTICK_RIGHT) == 0) D=1;
            if((joy1 & C64_JOYSTICK_BUTTON) == 0) D=999;
        }

        if((joy2 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
            if((joy1 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) evalKeyboard = true;
        }
        else {
            if((joy2 & C64_JOYSTICK_UP) == 0) D=2;
            else if((joy2 & C64_JOYSTICK_DOWN) == 0) D=3;
            else if((joy2 & C64_JOYSTICK_LEFT) == 0) D=0;
            else if((joy2 & C64_JOYSTICK_RIGHT) == 0) D=1;
            if((joy2 & C64_JOYSTICK_BUTTON) == 0) D=999;
        }

        //Evaluate keyboard if we get to here with no joystick input
        if(evalKeyboard) {
            switch(key) {
                case PKEY_NOKEY: break;
                case PKEY_A: D=0; break;
                case PKEY_D: D=1; break;
                case PKEY_Q: D=999; break;
                case PKEY_S: D=3; break;
                case PKEY_W: D=2; break;
                default: break;
            }
        }
    }

    return(D!=999);
}