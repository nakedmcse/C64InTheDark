#include <peekpoke.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Test loop for reading keyboard and josticks via memory mapping */

/* Joystick Macros */
#define C64_JOYSTICK_ADDRESS_1 56321U  // Control Port 1
#define C64_JOYSTICK_ADDRESS_2 56320U  // Control Port 2
#define C64_JOYSTICK_NONE     0x7F  //     0111 1111
#define C64_JOYSTICK_UP       0x01  // 254 1111 1110
#define C64_JOYSTICK_DOWN     0x02  // 253 1111 1101
#define C64_JOYSTICK_LEFT     0x04  // 251 1111 1011
#define C64_JOYSTICK_RIGHT    0x08  // 247 1111 0111
#define C64_JOYSTICK_BUTTON   0x10  // 239 1110 1111
#define GET_JOY1 PEEK(C64_JOYSTICK_ADDRESS_1)
#define GET_JOY2 PEEK(C64_JOYSTICK_ADDRESS_2)

/* Keyboard Macros */
#define GET_PKEY_VIEW PEEK(203)
#define PKEY_A           0x0A   // 'A'
#define PKEY_D           0x12   // 'D'
#define PKEY_S           0x0D   // 'S'
#define PKEY_W           0x09   // 'W'
#define PKEY_Q           0x3E   // 'Q'
#define PKEY_SPC         0x3C   // 'Spacebar'
#define PKEY_NOKEY       0x40   // No key pressed
#define CLRKEY \
__asm__("lda #$00"); \
__asm__("sta $c6");

/* Screen Macros */
#define BASE_SCREEN_ADDRESS 0x0400
#define BASE_COLOR_ADDRESS  0xD800

#define CLRSCR \
__asm__("lda #$93"); \
__asm__("jsr $ffd2");

#define SET_COLORS(border,back,text) \
    POKE(0xD020,border); \
    POKE(0xD021,back); \
    POKE(0x286,text);

#define SET_INK(text) \
    POKE(0x286,text);

int main() {
    unsigned char key,joy1,joy2;
    bool runloop = true;

    CLRSCR;

    while(runloop) {
        key = GET_PKEY_VIEW;
        joy1 = GET_JOY1;
        joy2 = GET_JOY2;

        switch(key) {
            case PKEY_NOKEY: printf("Key NOKEY "); break;
            case PKEY_A: printf("Key A "); break;
            case PKEY_D: printf("Key D "); break;
            case PKEY_Q: printf("Key Q"); runloop=false; break;
            case PKEY_S: printf("Key S "); break;
            case PKEY_W: printf("Key W "); break;
            case PKEY_SPC: printf("Key SPC "); break;
            default: printf("Key %02X ",key);
        }

        printf("Joy1 ");
        if((joy1 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
            printf("NONE ");
        }
        else {
            if((joy1 & C64_JOYSTICK_UP) == 0) printf("UP ");
            if((joy1 & C64_JOYSTICK_DOWN) == 0) printf("DOWN ");
            if((joy1 & C64_JOYSTICK_LEFT) == 0) printf("LEFT ");
            if((joy1 & C64_JOYSTICK_RIGHT) == 0) printf("RIGHT ");
            if((joy1 & C64_JOYSTICK_BUTTON) == 0) printf("FIRE ");
        }

        printf("Joy2 ");
        if((joy2 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
            printf("NONE ");
        }
        else {
            if((joy2 & C64_JOYSTICK_UP) == 0) printf("UP ");
            if((joy2 & C64_JOYSTICK_DOWN) == 0) printf("DOWN ");
            if((joy2 & C64_JOYSTICK_LEFT) == 0) printf("LEFT ");
            if((joy2 & C64_JOYSTICK_RIGHT) == 0) printf("RIGHT ");
            if((joy2 & C64_JOYSTICK_BUTTON) == 0) printf("FIRE ");
        }

        printf("\n");
        CLRKEY;
    }

    return 0;
}