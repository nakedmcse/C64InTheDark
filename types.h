/* Type definitions for objects */
#include <stdbool.h>

struct Room {
    int x1;
    int y1;
    int x2;
    int y2;
    bool Discovered;
    bool ShowContents;
    bool Changed;
};

struct Door {
    int x;
    iny y;
    int Room1I;
    int Room2I;
    bool Opened;
};

struct Item {
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
};

struct Player {
    int x;
    int y;
    int dx;
    int dy;
    int Room;
};

struct Monster {
    int x;
    int y;
    int dx;
    int dy;
    int Room;
};

/* Global Variables */
struct Room Rooms[10];
int RoomI;

struct Door Doors[40];
int DoorI;

struct Item Items[50];
int ItemI,CLight,CTreasure;

struct Monster Monsters[10];
int MonsterI;

struct Player CPlayer;
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