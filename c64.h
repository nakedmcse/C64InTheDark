/* C64 Specific Code */
#include<peekpoke.h>

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

/* Audio Macros */
#define AUDIO_C64_BASE_ADDR  0xD418
#define AUDIO_TURN_ON \
    POKE(56587U,16);
#define AUDIO_TURN_OFF \
    POKE(56587U,0);
#define AUDIO_INIT \
    POKE(AUDIO_C64_BASE_ADDR+24, 15);   \    // maximum volume	
	POKE(AUDIO_C64_BASE_ADDR+ 5,  0x0A0A); \ // ATTACK
	POKE(AUDIO_C64_BASE_ADDR+ 6,  0x0A0A);   // ATTACK
#define AUDIO_SET_OCTAVE(octave) \
    POKE(56586U,octave);
#define AUDIO_SET_FREQUENCY(freq) \
    POKE(56584U,freq);

/* Color Macros */
#define C64_COLOR_BLACK  0x00U
#define C64_COLOR_WHITE  0x01U
#define C64_COLOR_RED    0x02U
#define C64_COLOR_CYAN   0x03U
#define C64_COLOR_PURPLE 0x04U
#define C64_COLOR_GREEN  0x05U
#define C64_COLOR_BLUE   0x06U
#define C64_COLOR_YELLOW 0x07U
#define C64_COLOR_ORANGE 0x08U
#define C64_COLOR_BROWN  0x09U
#define C64_COLOR_PINK   0x0AU
#define C64_COLOR_DGREY  0x0BU
#define C64_COLOR_GREY   0x0CU
#define C64_COLOR_LGREEN 0x0DU
#define C64_COLOR_LBLUE  0x0EU
#define C64_COLOR_LGREY  0x0FU

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

#define GRAPHICS_ON \
    POKE(0xD018,21);

#define GRAPHICS_OFF \
    POKE(0xD018,23)

#define WRITE_CHAR(x,y,ch) \
    POKE(BASE_SCREEN_ADDRESS+(40*(y))+x, ch);

#define WRITE_1U_DIGIT(x,y,val) \
    WRITE_CHAR(x,y, 48 + val);