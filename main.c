#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

const int Mx = 1e4 + 10;
const double inF = 1e7 + 7;

struct game gameState;
int newGame = 1, wallForEachCell[100][100][5];
enum opponentType {human = 0, computer} opponent;

#include "raylib.h"
#include "structures.c"
#include "validwall.c"
#include "talisman.c"
#include "starting.c"
#include "HumanAndComputer.c"
#include "graphicHuman.c"
#include "minimax.c"
#include "graphicComputer.c"
#include "chooseOpponent.c"
#include "newGame.c"


int main() {

    FILE *inFile;
    inFile = fopen("gameState.dat", "rb");
    if (inFile) {
        fread(&gameState, sizeof(gameState), 1, inFile);
        if (!feof(inFile))
            newGame = getNewGame();
        fclose(inFile);
        inFile = fopen("gameState.dat", "wb");
        fclose(inFile);
    }

    if (newGame)
        opponent = getOpponentType();
    else {
        setWallaroundTheBoard();
        for (int i = 0; i < gameState.player1UsedWallNo; i++)
            blockCell(gameState.player1WallList[i]);
        for (int i = 0; i < gameState.player2UsedWallNo; i++)
            blockCell(gameState.player2WallList[i]);
        if (!strcmp(gameState.player2Name, "Mr. Jabal"))
            opponent = computer;
        else
            opponent = human;
    }

    switch (opponent) {
        case human:
            graphicHuman();
            break;
        case computer:
            graphicComputer();
            break;
    }

    return 0;
}

