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

/* Graphics */

void DrawRoom(Room *DR) {
    int i;
    unsigned char wallColor = L>0 ? C64_COLOR_GREEN : C64_COLOR_BLUE;

    if(DR->Discovered==true) {
        for(i=DR->x1; i<=DR->x2; i++) {
            POKE_INK(i,DR->y1,wallColor);
            WRITE_CHAR(i,DR->y1,ChHWall);
        }
        for(i=DR->y1+1; i<=DR->y2; i++) {
            POKE_INK(DR->x1,i,wallColor);
            POKE_INK(DR->x2,i,wallColor);
            WRITE_CHAR(DR->x1,i,ChVWall);
            WRITE_CHAR(DR->x2,i,ChVWall);
        }
        for(i=DR->x1; i<=DR->x2; i++) {
            POKE_INK(i,DR->y2,wallColor);
            WRITE_CHAR(i,DR->y2,ChHWall);
        }
    }
}

void DrawDoor(Door *DD) {
    unsigned char doorColor = L>0 ? C64_COLOR_BROWN : C64_COLOR_BLUE;
    if(((Rooms[DD->Room1I].Discovered==true)||(Rooms[DD->Room2I].Discovered)) && DD->Opened==false) {
        POKE_INK(DD->x,DD->y,doorColor);
        WRITE_CHAR(DD->x,DD->y,ChDoor);
    }
    else if(DD->Opened==true) {
        WRITE_CHAR(DD->x,DD->y,ChSpace);
    }
}

void DrawItem(int i) {
    if(Items[i].Redraw==true) {
        Items[i].Redraw=false;
        if(Items[i].IType==1) {
            POKE_INK(Items[i].x,Items[i].y,C64_COLOR_YELLOW);
            WRITE_CHAR(Items[i].x,Items[i].y,ChHash);
        } else if(Items[i].IType==2) {
            POKE_INK(Items[i].x,Items[i].y,C64_COLOR_YELLOW);
            WRITE_CHAR(Items[i].x,Items[i].y,ChDollar);
        }
        else {
            gotoxy(Items[i].x,Items[i].y);
            printf("%d",Items[i].IType);
        }
    }
}

void HideItem(int i) {
    if(Items[i].Redraw==true) {
        Items[i].Redraw=false;
        WRITE_CHAR(Items[i].x,Items[i].y,ChSpace);
    }
}

void DrawMonster(int i, char glyph) {
    if(!(Monsters[i].dx==CPlayer.x && Monsters[i].dy==CPlayer.y)) {
        WRITE_CHAR(Monsters[i].dx,Monsters[i].dy,ChSpace);
    }
    POKE_INK(Monsters[i].x,Monsters[i].y,C64_COLOR_WHITE);
    WRITE_CHAR(Monsters[i].x,Monsters[i].y,glyph);
    Monsters[i].dx=Monsters[i].x;
    Monsters[i].dy=Monsters[i].y;
}

void DrawMonsters() {
    char glyph;
    int i;

    for(i=0; i<=MonsterI; i++) {
        glyph=ChSpace;
        if((Rooms[Monsters[i].Room].ShowContents==true)&& L>0) {
            glyph=ChMonster;
        }
        DrawMonster(i,glyph);
    }
}

void DrawDungeon() {
    int i;
    bool newShowContents;

    for(i=0; i<=RoomI; i++) {
        newShowContents=CanSee(CPlayer.Room,i);
        Rooms[i].Changed=(newShowContents!=Rooms[i].ShowContents);
        Rooms[i].ShowContents=newShowContents;
        DrawRoom(&Rooms[i]);
    }

    for(i=0; i<=DoorI; i++) {
        DrawDoor(&Doors[i]);
    }

    for(i=0; i<ItemI; i++) {
        Items[i].Redraw = (Items[i].Redraw==true)||(Rooms[Items[I].Room].Changed==true);
        if((Rooms[Items[i].Room].ShowContents==false)||(Items[i].Taken==true)||(L==0)) {
            HideItem(i);
        }
        else {
            DrawItem(i);
        }
    }
}

void DrawFrame() {
    int x,y;
    char c;

    CLRSCR;
    for(x=0; x<SWidth-1; x++) {
        gotoxy(x,0);
        printf("%c",ChFrame);
        gotoxy(x,SHeight-1);
        printf("%c",ChFrame);
    }
    gotoxy(SWidth-1,0);
    printf("%c",ChFrame);

    c=PEEK(0x7E6);
    POKE(0x7E7,c);  //C64 specific - last screen char poked to avoid scroll

    for(y=0; y<SHeight-1; y++) {
        gotoxy(0,y);
        printf("%c",ChFrame);
        gotoxy(SWidth-1,y);
        printf("%c",ChFrame);
    }
    gotoxy(0,0);
}

void DrawPlayer() {
    WRITE_CHAR(CPlayer.dx,CPlayer.dy,ChSpace);
    POKE_INK(CPlayer.x,CPlayer.y,C64_COLOR_WHITE);
    WRITE_CHAR(CPlayer.x,CPlayer.y,ChPlayer);
    CPlayer.dx=CPlayer.x;
    CPlayer.dy=CPlayer.y;
}

void DrawStatus() {
    int i;

    for(i=0; i<SWidth-5; i++) {
        WRITE_CHAR(i,SHeight-1,ChSpace);
    }
    gotoxy(0,SHeight-1);

    if(MDist==0) {
        if(L==0) {
            printf("in the dark, grue talons drag you away.");
        }
        else {
            printf("you bump into a grue. Douses light, and you.");
        }
    }
    else if(MDist!=-1 && MDist<2 && L==0) {
        printf("grue breathing down your neck.");
    }
    else if(MDist!=-1 && MDist<4 && L==0) {
        printf("grue talons tapping the tiles nearby.");
    }
    else if(CT>0) {
        printf("found %s.",Noun[Items[CTreasure].D1]);
        CT--;
    }
    else {
        if(L==0) {
            printf("dark, grue coming for you.");
        }
        else if(L<5) {
            printf("%s grows dim. dark soon.",Noun[Items[CLight].D1]);
        }
        else {
            printf("%s lights your way",Noun[Items[CLight].D1]);
        }
    }
}

void DrawDebug() {
    gotoxy(0,SHeight-1);
    printf("room %d: %d,%d,%d,%d",CPlayer.Room,Rooms[CPlayer.Room].x1,Rooms[CPlayer.Room].y1,Rooms[CPlayer.Room].x2,Rooms[CPlayer.Room].y2);
}

void DrawDebugRooms() {
    int i=0;
    CLRSCR;

    for(i=0; i<=RoomI; i++) {
        printf("Room %d - %d,%d %d,%d Show %d Disc %d\n",i,Rooms[i].x1,Rooms[i].y1,Rooms[i].x2,Rooms[i].y2,Rooms[i].ShowContents,Rooms[i].Discovered);
    }
}

void DrawDebugItems() {
    int i=0;
    CLRSCR;

    for(i=0; i<=ItemI; i++) {
        printf("Item %d - Room %d %d,%d Type %d Taken %d\n",i,Items[i].Room,Items[i].x,Items[i].y,Items[i].IType,Items[i].Taken);
    }
}

void DrawScore() {
    int i;

    gotoxy(SWidth-6, SHeight-1);
    for(i=0; i<5; i++) {
        printf("%c",ChFrame);
    }
    gotoxy(SWidth-6, SHeight-1);
    printf("%d/%d",T,DT);

    gotoxy(SWidth-12,0);
    printf("dungeon: %d",DC+1);
}