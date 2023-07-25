#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "types.h"
//#include "all.h"
//#include "items.h"
//#include "room.h"

/* monster mash */

void GenerateMonsters() {
    int i,p,hiti;
    bool valid;

    MDist=-1;
    MonsterI=0;

    for(i=0; i<=RoomI; i++) {
        valid=false;
        p=rand() % 100;
        if(p>60) {
            while(valid==false) {
                Monsters[MonsterI].dx=(rand() % (Rooms[i].x2-Rooms[i].x1-2)) + Rooms[i].x1 + 1;
                Monsters[MonsterI].dy=(rand() % (Rooms[i].y2-Rooms[i].y1-2)) + Rooms[i].y1 + 1;
                Monsters[MonsterI].x=Monsters[MonsterI].dx;
                Monsters[MonsterI].y=Monsters[MonsterI].dy;
                Monsters[MonsterI].Room = i;
                hiti=HitItem(Monsters[MonsterI].x,Monsters[MonsterI].y);
                if((Monsters[MonsterI].x!=CPlayer.x) && (Monsters[MonsterI].y!=CPlayer.y) && (hiti==-1)) {
                    valid=true;
                }
            }
            MonsterI++;
        }
    }
    MonsterI--; //we end up with +1, so need to sub
}

void MoveRandom(int i) {
    int tries,d,tx,ty;
    bool valid=false;

    d = rand() % 3;
    tries = 0;
    while(tries<5 && valid==false) {
        tries++;
        if(tries!=1) d=(d+1)%4;  //try next direction
        tx=Monsters[i].x;
        ty=Monsters[i].y;
        if(d==0) {
            tx--;
        }
        else if(d==1) {
            tx++;
        }
        else if(d==2) {
            ty--;
        }
        else if(d==3) {
            ty++;
        };
        valid = (HitWall(tx,ty)==false) && (HitItem(tx,ty)==-1);
    }

    if(valid==true) {
        Monsters[i].x=tx;
        Monsters[i].y=ty;
    }
}

void MoveToPlayer(int i, int d) {
    int cx,cy,tx,ty;

    cx = Monsters[i].x - CPlayer.x;
    cy = Monsters[i].y - CPlayer.y;

    if(cx!=0 && cy!=0) {
        tx=Monsters[i].x;
        ty=Monsters[i].y;
        if(abs(cx)>abs(cy)) {
            if(cx>0) {
                tx=Monsters[i].x-d;
            }
            else {
                tx=Monsters[i].x+d;
            }
        }
        else {
            if(cy>0) {
                ty=Monsters[i].y-d;
            }
            else {
                ty=Monsters[i].y+d;
            }
        }

        if((HitWall(tx,ty)==false) && (HitItem(tx,ty)==-1)) {
            Monsters[i].x=tx;
            Monsters[i].y=ty;
        }
        else {
            MoveRandom(i);
        }
    }
}

void MoveMonsters() {
    int i;
    int d=-1;  //d = 1 to player, -1 away from player

    if(L==0) d=1;

    for(i=0; i<=MonsterI; i++) {
        if(Monsters[i].Room==CPlayer.Room) {
            MoveToPlayer(i,d);
        }
        else {
            MoveRandom(i);
        }
    }
}

/* HitMonster returns -1 if not hit or int of distance if within 4 chars */
int HitMonster(int x1, int y1) {
    int cx,cy;
    int i=0;
    bool found=false;

    while(i<=MonsterI && found==false) {
        if(Monsters[i].Room==HitRoom(x1,y1)) {
            cx=abs(x1-Monsters[i].x);
            cy=abs(y1-Monsters[i].y);
            if(cx<4 && cy<4) {
                found=true;
            }
            else {
                i++;
            }
        }
        else {
            i++;
        }
    }

    if(found==true) return Max(cx,cy);
    return -1;
}