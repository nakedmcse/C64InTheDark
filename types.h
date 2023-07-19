/* Type definitions for objects */
#include <stdbool.h>

typedef struct Room {
    int x1;
    int y1;
    int x2;
    int y2;
    bool Discovered;
    bool ShowContents;
    bool Changed;
} Room;

typedef struct Door {
    int x;
    int y;
    int Room1I;
    int Room2I;
    bool Opened;
} Door;

typedef struct Item {
    int x;
    int y;
    int Room;
    int IType;
    int L;
    int T;
    int D1;
    int D2;
    bool Taken;
    bool Redraw;
} Item;

typedef struct Player {
    int x;
    int y;
    int dx;
    int dy;
    int Room;
} Player;

typedef struct Monster {
    int x;
    int y;
    int dx;
    int dy;
    int Room;
} Monster;

/* Global Variables */
Room Rooms[10];
int RoomI;

Door Doors[40];
int DoorI;

Item Items[50];
int ItemI,CLight,CTreasure;

Monster Monsters[10];
int MonsterI;

Player CPlayer;
int D,MDist,I,L,T,DT,CT;

int DC;
bool NextDungeon;

/* Constants */
const int SWidth = 40;
const int SHeight = 25;
const int LWidth = 5;
const int LHeight = 5;
const int UWidth = 10;
const int UHeight = 10;
const int MWidth = 3;
const int MHeight = 3;

const char ChSpace = 32;
const char ChMonster = 34;
const char ChHash = 35;
const char ChDollar = 36;
const char ChDoor = 118;
const char ChVWall = 166;
const char ChHWall = 166;
const char ChFrame = 42;
const char ChPlayer = 119;

/* Dictionarys for nouns and verbs*/
char Noun[20][19] = {
    "match",
    "candle",
    "glow worms",
    "branch",
    "squash",
    "bulb",
    "torch",
    "rock",
    "torch",
    "brass lantern",
    "painting",
    "egg",
    "jewel",
    "belt buckle",
    "casket",
    "crystal skull",
    "pearl",
    "piece of eight",
    "fish scale",
    "carpenters chalice"
};

char Adjective[20][19] = {
    "glimmering",
    "shimmering",
    "bright",
    "golden",
    "sparkling",
    "battery powered",
    "radiant",
    "luminos",
    "flashing",
    "brilliant",
    "wooden",
    "illustrated",
    "golden",
    "bejewled",
    "plain",
    "resplendant",
    "ghostly",
    "oozing",
    "gigantic",
    "clockwork"
};