#include "types.h"
#include "all.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* room and door generation */

/* generate first room */
void FirstRoom() {
    int W,H;
    RoomI = 0;
    Rooms[0].Discovered = false;
    Rooms[0].ShowContents = true;
    Rooms[0].x1 = (rand() % (SWidth-UWidth-1))+1;
    Rooms[0].y1 = (rand() % (SHeight-UHeight -1))+1;
    W = (rand() % (UWidth-LWidth)) + LWidth + 1;
    H = (rand() % (UHeight-LHeight)) + LHeight +1;
    Rooms[0].x2 = Rooms[0].x1 + W;
    Rooms[0].y2 = Rooms[0].y1 + H;
};

/* Check room overlap */
bool Overlap(Room* SR,Room* DR) {
    if((SR->x1<DR->x2) && (SR->x2>DR->x1) && (SR->y1<DR->y2) && (SR->y2>DR->y1)) {
        return true;
    };
    return false;
};

/* Check x,y to see if it hits a wall */
bool HitWall(int x, int y) {
    bool found = false;
    int i = 0;
    while (i<=RoomI && !found) {
        if((x>=Rooms[i].x1 && x<=Rooms[i].x2 && (y==Rooms[i].y1 || y==Rooms[i].y2)) ||
            (y>=Rooms[i].y1 && y<=Rooms[i].y2 && (x==Rooms[i].x1 || x==Rooms[i].x2))) {
                found=true;
            }
        else {
            i++;
        }
    }
    return found;
};

/* Check x,y to see if hit door, if so return index, -1 on fail */
int HitDoor(int x, int y) {
    bool found = false;
    int i = 0;
    while (i<=DoorI && !found) {
        if(Doors[i].x==x && Doors[i].y==y) {
            found=true;
        }
        else {
            i++;
        }
    }
    if (found) return i;
    return -1;
};

/* Check x,y to see if in room, if so return index, -1 on fail */
int HitRoom(int x, int y) {
    bool found = false;
    int i = 0;
    while (i<=RoomI && !found) {
        if(x>Rooms[i].x1 && x<Rooms[i].x2 && y>Rooms[i].y1 && y<Rooms[i].y2) {
            found=true;
        }
        else {
            i++;
        }
    }
    if (found) return i;
    return -1;
};

/* Check if Room Target can be seen from Room Index */
bool CanSee(int RI,int RT) {
    bool found = false;
    int i = 0;
    if(RI=RT) return true;
    while (i<=DoorI && !found) {
        if(((Doors[i].Room1I==RI && Doors[i].Room2I==RT)||(Doors[i].Room1I==RT && Doors[i].Room2I==RI)) && Doors[i].Opened) {
            found=true;
        }
        else {
            i++;
        }
    }
    return found;
};

/* Door not found */
bool DoorNotFound(int Room1, int Room2) {
    bool found = false;
    int i = 0;
    while (i<DoorI && found==false) {
        if((Doors[i].Room1I==Room1 && Doors[i].Room2I==Room2)||(Doors[i].Room1I==Room2 && Doors[i].Room2I==Room1)) {
            found=true;
        }
        else {
            i++;
        }
    }
    if(found) return false;
    return true;
};

int RandomInRange(int min1, int min2, int max1, int max2) {
    int amin = Max(min1,min2)+1;
    int amax = Min(max1,max2)-1;
    int a = amax-amin;
    if(a>0) {
        return(amin + (rand() % a));
    }
    return amin;
};

void GenerateDoors() {
    int i,j;
    Room cr;
    Room tr;

    DoorI = 0;
    for(i=0; i<=RoomI; i++) {
        cr = Rooms[i];
        for(j=0; j<=i; j++) {
            tr = Rooms[j];
            Doors[DoorI].Room1I=i;
            Doors[DoorI].Room2I=j;
            Doors[DoorI].Opened=false;
            if(DoorNotFound(i,j)) {
                if(cr.x2==tr.x1 && tr.y1<cr.y2 && tr.y2>cr.y1) {
                    Doors[DoorI].x=cr.x2;
                    Doors[DoorI].y=RandomInRange(cr.y1,tr.y1,cr.y2,tr.y2);
                    DoorI++;
                }
                else if(cr.x1==tr.x2 && tr.y1<cr.y2 && tr.y2>cr.y1) {
                    Doors[DoorI].x=cr.x1;
                    Doors[DoorI].y=RandomInRange(cr.y1,tr.y1,cr.y2,tr.y2);
                    DoorI++;
                }
                else if(cr.y2==tr.y1 && tr.x1<cr.x2 && tr.x2>cr.x1) {
                    Doors[DoorI].y=cr.y2;
                    Doors[DoorI].x=RandomInRange(cr.x1,tr.x1,cr.x2,tr.x2);
                    DoorI++;
                }
                else if(cr.y1==tr.y2 && tr.x1<cr.x2 && tr.x2>cr.x1) {
                    Doors[DoorI].y=cr.y1;
                    Doors[DoorI].x=RandomInRange(cr.x1,tr.x1,cr.x2,tr.x2);
                    DoorI++;
                }
            }
        }
    }
    DoorI--;
};

/* generate next room */
bool NextRoom() {
    int w,h,x,y,d,ds,i;
    bool TryAgain,GenNext;
    Room cr;

    d = (rand() % 4);
    ds = d;
    cr = Rooms[RoomI];
    TryAgain = true;

    while(TryAgain) {
        w=(rand() % (UWidth-LWidth))+LWidth+1;
        h=(rand() % (UHeight-LHeight))+LHeight+1;
        Rooms[RoomI+1].Discovered=false;
        Rooms[RoomI+1].ShowContents=true;
        GenNext=true;
        if(d==0) {
            Rooms[RoomI+1].x2=cr.x1;
            if(Rooms[RoomI+1].x2 - w < 1) w=Rooms[RoomI+1].x2-1;
            if(w<LWidth) GenNext=false;
            Rooms[RoomI+1].x1=Rooms[RoomI+1].x2-w;
            y=(rand() % (cr.y2-cr.y1-1))+cr.y1+1;
            if(y-(h/2)<1) h=y;
            if(y-(h/2)+h>=SHeight) h=SHeight-y-1;
            if(h<MHeight) GenNext=false;
            Rooms[RoomI+1].y1=y-(h/2);
            Rooms[RoomI+1].y2=Rooms[RoomI+1].y1+h;
        }
        else if(d==1) {
            Rooms[RoomI+1].x1=cr.x2;
            if(Rooms[RoomI+1].x1 + w > SWidth) w=SWidth-Rooms[RoomI+1].x1;
            if(w<LWidth) GenNext=false;
            Rooms[RoomI+1].x2=Rooms[RoomI+1].x1+w;
            y=(rand() % (cr.y2-cr.y1-1))+cr.y1+1;
            if(y-(h/2)<1) h=y;
            if(y-(h/2)+h>=SHeight) h=SHeight-y-1;
            if(h<MHeight) GenNext=false;
            Rooms[RoomI+1].y1=y-(h/2);
            Rooms[RoomI+1].y2=Rooms[RoomI+1].y1+h;
        }
        else if(d==2) {
            Rooms[RoomI+1].y2=cr.y1;
            if(Rooms[RoomI+1].y2-h<1) h=Rooms[RoomI+1].y2-1;
            if(h<LHeight) GenNext=false;
            Rooms[RoomI+1].y1=Rooms[RoomI+1].y2-h;
            x=(rand() % (cr.x2-cr.x1-1))+cr.x1+1;
            if(x-(w/2)<1) w=x;
            if(x-(w/2)+w>=SWidth) w=SWidth-x-1;
            if(w<MWidth) GenNext=false;
            Rooms[RoomI+1].x1 = x-(w/2);
            Rooms[RoomI+1].x2 = Rooms[RoomI+1].x1 + w;
        }
        else if(d==3) {
            Rooms[RoomI+1].y1=cr.y2;
            if(Rooms[RoomI+1].y1+h>SHeight) h=SHeight-Rooms[RoomI+1].y1;
            if(h<LHeight) GenNext=false;
            Rooms[RoomI+1].y2=Rooms[RoomI+1].y1+h;
            x=(rand() % (cr.x2-cr.x1-1))+cr.x1+1;
            if(x-(w/2)<1) w=x;
            if(x-(w/2)+w>=SWidth) w=SWidth-x-1;
            if(w<MWidth) GenNext=false;
            Rooms[RoomI+1].x1 = x-(w/2);
            Rooms[RoomI+1].x2 = Rooms[RoomI+1].x1 + w;
        }

        for(i=0; i<=RoomI; i++) {
            if(Overlap(&Rooms[i],&Rooms[RoomI+1])) {
                if(Rooms[RoomI+1].y2 > Rooms[i].y1) {
                    Rooms[RoomI+1].y2 = Rooms[i].y1;
                }
                else if(Rooms[RoomI+1].y1 < Rooms[i].y2) {
                    Rooms[RoomI+1].y1 = Rooms[i].y2;
                }
                else if(Rooms[RoomI+1].x2 > Rooms[i].x1) {
                    Rooms[RoomI+1].x2 = Rooms[i].x1;
                }
                else if(Rooms[RoomI+1].x1 < Rooms[i].x2) {
                    Rooms[RoomI+1].x1 = Rooms[i].x2;
                }
                w=Rooms[RoomI+1].x2-Rooms[RoomI+1].x1;
                h=Rooms[RoomI+1].y2-Rooms[RoomI+1].y1;
                if(w<MWidth || h<MHeight) GenNext=false;
            }
        }

        if(GenNext) {
            TryAgain=false;
        }
        else {
            d = (d+1)%4;
            if(d==ds) TryAgain=false;
        }
    }

    if(GenNext) RoomI++;
    return GenNext;
};

void GenerateDungeon() {
    int attempt=1;
    RoomI=0;
    while(RoomI<5) {
        printf("Attempt %d,%d...\n",attempt,RoomI);
        FirstRoom();
        while(RoomI<10 && NextRoom()) {};
        printf("Rooms %d\n",RoomI);
        attempt++;
    }
    printf("Generating Doors\n");
    GenerateDoors();
}