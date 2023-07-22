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

/* input handling */
bool NextMove() {
    char ch;

    D=-1;
    ch=cgetc();

    if(ch=='a') {
        D=0;
    }
    else if(ch=='s') {
        D=3;
    }
    else if(ch=='d') {
        D=1;
    }
    else if(ch=='w') {
        D=2;
    }
    else if(ch=='q') {
        D=999;
    };

    return(D!=999);
}