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

#include "raylib.h"
#include "structures.c"
#include "validwall.c"
#include "talisman.c"
#include "starting.c"
#include "HumanAndComputer.c"
#include "minimax.c"
#include "graphicComputer.c"
#include "playerCount.c"
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

    if (newGame) {
        gameState.playerCount = getPlayerCount();
        gameState.player1Type = 0;
        if (gameState.playerCount == 2)
            gameState.player2Type = getOpponentType(2);
        else {
            gameState.player2Type = getOpponentType(2);
            gameState.player3Type = getOpponentType(3);
            gameState.player4Type = getOpponentType(4);
        }
    }
    else {
        setWallaroundTheBoard();
        for (int i = 0; i < gameState.player1UsedWallNo; i++)
            blockCell(gameState.player1WallList[i]);
        for (int i = 0; i < gameState.player2UsedWallNo; i++)
            blockCell(gameState.player2WallList[i]);
        for (int i = 0; i < gameState.player3UsedWallNo; i++)
            blockCell(gameState.player3WallList[i]);
        for (int i = 0; i < gameState.player4UsedWallNo; i++)
            blockCell(gameState.player4WallList[i]);
    }

    graphicComputer();

    return 0;
}

