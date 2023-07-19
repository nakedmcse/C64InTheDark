/* In The Dark C64 */
#include "c64.h"
#include "room.h"
#include<stdio.h>
#include<conio.h>

int main(void) {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    printf("Generating Dungeon...\n");
    GenerateDungeon();
    printf("Generated %d rooms\n",RoomI);
    printf("Generated %d doors\n",DoorI);
    while(true) {};
    return EXIT_SUCCESS;
}