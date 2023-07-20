#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "types.h"
//#include "all.h"

/* Items */

void GenerateLight(int i) {
    int p,du,dl;
    p = (rand() % 99);
    if(p>95) {
        dl=9;
        du=10;
    }
    else if(p>90) {
        dl=7;
        du=9;
    }
    else if(p>80) {
        dl=8;
        du=8;
    }
    else if(p>60) {
        dl=2;
        du=5;
    }
    else {
        dl=1;
        du=3;
    }

    Items[i].IType=1; //light
    Items[i].Taken=false;
    Items[i].L = ((rand() % (du-dl))+dl) * (16/Min(DC+1,16));
    Items[i].T = 0;
    Items[i].D1 = (rand() % (du-dl))+dl;
    Items[i].D2 = rand() % 10;
}

void GenerateTreasure(int i) {
    Items[i].IType=2; //treasure
    Items[i].Taken=false;
    Items[i].L = 0;
    Items[i].T = 1;
    Items[i].D1 = (rand() % 10)+10;
    Items[i].D2 = (rand() % 10)+10;
    DT++;
}

int HitItem(int x1,int y1) {
    int i = 1;
    bool found = false;
    if(ItemI>0) {
        while(i<=ItemI && found==false) {
            if(Items[i].x==x1 && Items[i].y==y1 && Items[i].Taken==false) {
                found=true;
            }
            else {
                i++;
            }
        }
    }
    if(found==true) return i;
    return -1;
}

void GenerateItems() {
    int i,j,p;
    bool valid;

    CLight=-1;
    CTreasure=-1;
    GenerateLight(0); //first light

    ItemI=0;
    T=0;
    DT=0;
    CT=0;

    for(i=0; i<=RoomI; i++) {
        for(j=0; j<=4; j++) {
            valid=false;
            while(valid==false) {
                valid=true;
                p = rand() % 100;
                if(p>40) {
                    Items[ItemI+1].Redraw=true;
                    Items[ItemI+1].x=(rand() % (Rooms[i].x2-Rooms[i].x1-2)) + Rooms[i].x1 + 1;
                    Items[ItemI+1].y=(rand() % (Rooms[i].y2-Rooms[i].y1-2)) + Rooms[i].y1 + 1;
                    Items[ItemI+1].Room = i;
                    if(HitItem(Items[ItemI+1].x,Items[ItemI+1].y)>-1) valid=false;
                    if(valid==true) {
                        if(p>80) {
                            GenerateTreasure(ItemI+1);
                        }
                        else {
                            GenerateLight(ItemI+1);
                        }
                        ItemI++;
                    }
                }
            }
        }
    }
}

void SetAllRedraw() {
    int i;
    for(i=1; i<=ItemI; i++) {
        Items[i].Redraw=true;
    }
}

void TakeItem(int i) {
    Items[i].Taken=true;
    Items[i].Redraw=true;
    if(Items[i].L>0) {
        SetAllRedraw();
        L=Items[i].L;
        CLight=i;
    }
    if(Items[i].T>0) {
        T=T+Items[i].T;
        CTreasure=i;
        CT=3;
    }
}