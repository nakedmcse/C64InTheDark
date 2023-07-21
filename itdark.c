/* In The Dark C64 */
#include "c64.h"
#include "all.h"
#include "types.h"
#include "room.h"
#include "items.h"
#include "monster.h"
#include "player.h"
#include "graphics.h"
#include<stdio.h>
#include<conio.h>

int main(void) {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    _randomize();
    printf("Generating Dungeon...\n");
    GenerateDungeon();
    printf("Generated %d rooms\n",RoomI);
    printf("Generated %d doors\n",DoorI);
    GenerateItems();
    printf("Generated %d items\n",ItemI);
    GeneratePlayer();
    printf("Spawned player in room %d at %d,%d\n",CPlayer.Room,CPlayer.dx,CPlayer.dy);
    GenerateMonsters();
    printf("Spawned %d monsters\n",MonsterI);
    
    GRAPHICS_ON;
    DrawFrame();
    DrawDungeon();
    DrawPlayer();
    DrawMonsters();
    //DrawStatus();
    DrawDebug();
    DrawScore();

    while(true) {};
    GRAPHICS_OFF;
    return EXIT_SUCCESS;
}