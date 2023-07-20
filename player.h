#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "types.h"
//#include "all.h"
//#include "items.h"
//#include "room.h"

/* Player code */

void GeneratePlayer() {
    int i;
    bool valid=false;
    i = rand() % RoomI;

    while(valid==false) {
        CPlayer.dx=(rand() % (Rooms[i].x2-Rooms[i].x1-2)) + Rooms[i].x1 + 1;
        CPlayer.dy=(rand() % (Rooms[i].y2-Rooms[i].y1-2)) + Rooms[i].y1 + 1;
        if(HitItem(CPlayer.dx,CPlayer.dy)==-1) valid=true;
        if(valid==true) {
            CPlayer.x=CPlayer.dx;
            CPlayer.y=CPlayer.dy;
            CPlayer.Room = i;
            Rooms[i].Discovered=true;
        }
    }

    TakeItem(0);
}

bool MovePlayer() {
    int x,y,FoundDoorI,FoundItemI,NewRoom;
    bool redraw,valid;

    x=CPlayer.x;
    y=CPlayer.y;
    redraw=false;
    valid=true;

    if(D>=0 && D<4) {
        if(D==0) {
            x=CPlayer.x-1;
        }
        else if(D==1) {
            x=CPlayer.x+1;
        }
        else if(D==2) {
            y=CPlayer.y-1;
        }
        else if(D==3) {
            y=CPlayer.y+1;
        }

        FoundDoorI=HitDoor(x,y);
        if(FoundDoorI>-1) {
            Rooms[Doors[FoundDoorI].Room1I].Discovered=true;
            Rooms[Doors[FoundDoorI].Room2I].Discovered=true;
            Doors[FoundDoorI].Opened=true;
            redraw=true;
        }

        valid=(HitWall(x,y)==false);
        if(valid==true) {
            CPlayer.x=x;
            CPlayer.y=y;

            NewRoom = HitRoom(x,y);
            if(NewRoom>-1 && CPlayer.Room!=NewRoom) {
                CPlayer.Room=NewRoom;
                redraw=true;
            }

            FoundItemI=HitItem(x,y);
            if(FoundItemI>-1) {
                TakeItem(FoundItemI);
                redraw=true;
            }
            else {
                if(L>0) L--;
                if(L==0) {
                    //Lights out
                    SetAllRedraw();
                    redraw=true;
                }
            }
            //MoveMonsters goes here
        }
    }
    return redraw;
}