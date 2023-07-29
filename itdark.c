/* In The Dark C64 */
#include "c64.h"
#include "all.h"
#include "types.h"
#include "room.h"
#include "items.h"
#include "monster.h"
#include "player.h"
#include "graphics-poke.h"
#include "input.h"
#include<stdio.h>
#include<conio.h>

int main(void) {
    int line,col,droll;
    unsigned char CHBan;
    bool NextDungeon = true;

    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    _randomize();
    MDist=0;
    CT=0;
    T=0;
    DC=0;

    while(NextDungeon==true) {
        if (DC==0) {
            //Banner
            for(line=0; line<5; line++) {
                for(col=0; col<SWidth; col++) {
                    droll = rand() % 10;
                    CHBan = droll<=5 ? 95 : 105;
                    WRITE_CHAR(col,line,CHBan);
                }
            }
            SET_INK(C64_COLOR_WHITE);
            gotoxy(12,2);
            printf("-* IN THE DARK *-");
            SET_INK(C64_COLOR_GREEN);
            gotoxy(0,6);
        }
        printf("Generating Dungeon...\n");
        GenerateDungeon();
        printf("Generated %d rooms\n",RoomI+1);
        printf("Generated %d doors\n",DoorI+1);
        GenerateItems();
        printf("Generated %d items\n",ItemI+1);
        GeneratePlayer();
        printf("Spawned player in room %d at %d,%d\n",CPlayer.Room,CPlayer.dx,CPlayer.dy);
        GenerateMonsters();
        printf("Spawned %d monsters\n",MonsterI+1);

        if(DC==0) {
            //Instructions
            printf("\nw,s,a,d or joystick for movement\n");
            printf("q or fire to quit\n");
            printf("move to start!\n");
            NextMove();
        }
    
        CLRSCR;
        GRAPHICS_ON;
        DrawDungeon();
        DrawPlayer();
        DrawMonsters();
        DrawStatus();
        DrawScore();

        while(MDist!=0 && T<DT && NextMove()) {
            if(MovePlayer()==true) DrawDungeon();
            DrawPlayer();
            DrawMonsters();
            MDist=HitMonster(CPlayer.x,CPlayer.y);
            DrawStatus();
            DrawScore();
        }

        if(T<DT) {
            NextDungeon=false;
        }
        else {
            DC++;
            CLRSCR;
            SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
            _randomize();
        }
        GRAPHICS_OFF;
    }

    //Debug Info
    DrawDebugRooms();
    NextMove();
    DrawDebugItems();
    NextMove();
    return EXIT_SUCCESS;
}