/* In The Dark C64 */
#include "all.h"
#include "c64.h"
#include "types.h"
#include "room.h"

int main(void) {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    printf("Generating Dungeon...\n");
    GenerateDungeon();
    printf("Generated %d rooms",RoomI);
    printf("Generated %d doors",DoorI);
    return EXIT_SUCCESS;
}