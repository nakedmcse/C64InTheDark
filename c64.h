/* C64 Specific Code */
#include<peekpoke.h>

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