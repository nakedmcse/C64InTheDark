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

    if(DR->Discovered==true) {
        gotoxy(DR->x1,DR->y1);
        for(i=DR->x1; i<=DR->x2; i++) {
            printf("%c",ChHWall);
        }
        for(i=DR->y1+1; i<=DR->y2; i++) {
            gotoxy(DR->x1,i);
            printf("%c",ChVWall);
            gotoxy(DR->x2,i);
            printf("%c",ChVWall);
        }
        gotoxy(DR->x1,DR->y2);
        for(i=DR->x1; i<=DR->x2; i++) {
            printf("%c",ChHWall);
        }
    }
}

void DrawDoor(Door *DD) {
    if(((Rooms[DD->Room1I].Discovered==true)||(Rooms[DD->Room2I].Discovered)) && DD->Opened==false) {
        gotoxy(DD->x,DD->y);
        printf("%c",ChDoor);
    }
    else if(DD->Opened==true) {
        gotoxy(DD->x,DD->y);
        printf("%c",ChSpace);
    }
}

void DrawItem(int i) {
    if(Items[i].Redraw==true) {
        Items[i].Redraw=false;
        gotoxy(Items[i].x,Items[i].y);
        if(Items[i].IType==1) {
            printf("%c",ChDollar);
        } else if(Items[i].IType==2) {
            printf("%c",ChHash);
        }
        else {
            printf("%d",Items[i].IType);
        }
    }
}

void HideItem(int i) {
    if(Items[i].Redraw==true) {
        Items[i].Redraw=false;
        gotoxy(Items[i].x,Items[i].y);
        printf("%c",ChSpace);
    }
}

void DrawMonster(int i, char glyph) {
    gotoxy(Monsters[i].dx,Monsters[i].dy);
    if(!(Monsters[i].dx==CPlayer.x && Monsters[i].dy==CPlayer.y)) {
        printf("%c",ChSpace);
    }
    gotoxy(Monsters[i].x,Monsters[i].y);
    printf("%c",glyph);
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
        SET_INK(C64_COLOR_BROWN);
        DrawDoor(&Doors[i]);
        SET_INK(C64_COLOR_GREEN);
    }

    for(i=0; i<ItemI; i++) {
        Items[i].Redraw = (Items[i].Redraw==true)||(Rooms[Items[I].Room].Changed==true);
        if((Rooms[Items[i].Room].ShowContents==false)||(Items[i].Taken==true)||(L==0)) {
            HideItem(i);
        }
        else {
            SET_INK(C64_COLOR_YELLOW);
            DrawItem(i);
            SET_INK(C64_COLOR_GREEN);
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
    gotoxy(CPlayer.dx,CPlayer.dy);
    printf("%c",ChSpace);
    gotoxy(CPlayer.x,CPlayer.y);
    SET_INK(C64_COLOR_WHITE);
    printf("%c",ChPlayer);
    SET_INK(C64_COLOR_GREEN);
    CPlayer.dx=CPlayer.x;
    CPlayer.dy=CPlayer.y;
}

void DrawStatus() {
    int i;

    gotoxy(0,SHeight-1);
    for(i=0; i<SWidth-1; i++) {
        printf("%c",ChFrame);
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