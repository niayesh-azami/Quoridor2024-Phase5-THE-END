enum talisman {removeAllWalls = 0, decreaseWallNo, blockTurn, increaseWallNo, specialIncreaseWallNo} talismanType;
int value[5] = {2, 3, 5};
int indx = 0, specialValue;

void generateTalismanPosition() {
    time_t t;
    srand((unsigned) time(&t));

    memset(gameState.talismans, 0, sizeof(gameState.talismans));

    for (int i = 0; i < (gameState.size * 5) / 2; i++) {
        int x = rand() % gameState.size;
        int y = rand() % gameState.size;
        if (!gameState.talismans[x][y] && !(x == gameState.size / 2 && (!y || y == gameState.size - 1)))
            gameState.talismans[x][y] = 1;
        else
            i--;
    }
}

void applyTalisman() {
    time_t t;
    srand((unsigned) time(&t));

    talismanType = rand() % 5;

    switch (talismanType) {
        case removeAllWalls:
            for (int i = 0; i < gameState.player1UsedWallNo; i++)
                unBlockCell(gameState.player1WallList[i]);
            for (int i = 0; i < gameState.player2UsedWallNo; i++)
                unBlockCell(gameState.player2WallList[i]);
            gameState.player1WallNo -= gameState.player1UsedWallNo;
            gameState.player2WallNo -= gameState.player2UsedWallNo;
            gameState.player1UsedWallNo = 0;
            gameState.player2UsedWallNo = 0;
            break;
        case decreaseWallNo:
            indx = rand() % 3;
            if(!gameState.turnSw) {
                gameState.player2WallNo -= value[indx];
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
            }
            else {
                gameState.player1WallNo -= value[indx];
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
            }
            break;
        case blockTurn:
            specialValue = rand() % 2 + 1;
            if (!gameState.turnSw)
                gameState.player2BlockCount += specialValue;
            else
                gameState.player1BlockCount += specialValue;
            break;
        case increaseWallNo:
            indx = rand() % 3;
            if(!gameState.turnSw)
                gameState.player2WallNo += value[indx];
            else
                gameState.player1WallNo += value[indx];
            break;
        case specialIncreaseWallNo:
            specialValue = rand() % 2 + 1;
            if (!gameState.turnSw) {
                gameState.player2WallNo += specialValue;
                gameState.player1WallNo -= specialValue;
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
            }
            else {
                gameState.player1WallNo += specialValue;
                gameState.player2WallNo -= specialValue;
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
            }
            break;
    }
}
