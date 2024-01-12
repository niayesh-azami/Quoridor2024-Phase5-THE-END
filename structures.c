struct position {
    int x, y;
};

struct wall {
    char dir;
    int x, y;
};

struct game {
    int size;
    int playerCount;
    struct position player1Pos, player2Pos, player3Pos, player4Pos;
    int player1Type, player2Type, player3Type, player4Type;
    int player1WallNo;
    int player2WallNo;
    int player3WallNo;
    int player4WallNo;
    int player1UsedWallNo;
    int player2UsedWallNo;
    int player3UsedWallNo;
    int player4UsedWallNo;
    struct wall player1WallList[100 + 10];
    struct wall player2WallList[100 + 10];
    struct wall player3WallList[100 + 10];
    struct wall player4WallList[100 + 10];
    char player1Name[50];
    char player2Name[50];
    char player3Name[50];
    char player4Name[50];
    int turnSw;
    int talismans[100 + 10][100 + 10];
    int playerBlockCount[5];
};

struct stringInStartingScreen {
    char value[50];
    int realLength;
    int validLength;
    int isSet;
    int validLengthEx;
    char validValueS;
    char validValueE;
};

struct move {
    char type;
    struct position playerPos;
    struct wall wallPos;
};