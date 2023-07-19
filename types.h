/* Type definitions for objects */
struct Room {
    int x1, y1, x2, y2;
    bool Discovered,ShowContents,Changed;
};

struct Door {
    int x,y,Room1I,Room2I;
    bool Opened;
};

struct Item {
    int x,y,Room,IType,L,T,D1,D2;
    bool Taken,Redraw;
};

struct Player {
    int x,y,dx,dy,Room;
};

struct Monster {
    int x,y,dx,dy,Room;
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