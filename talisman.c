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
        if (!gameState.talismans[x][y] && !(x == gameState.size / 2 && (!y || y == gameState.size - 1)) && !(y == gameState.size / 2 && (!x || x == gameState.size - 1)))
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
            if (gameState.playerCount) {
                for (int i = 0; i < gameState.player3UsedWallNo; i++)
                    unBlockCell(gameState.player3WallList[i]);
                for (int i = 0; i < gameState.player4UsedWallNo; i++)
                    unBlockCell(gameState.player4WallList[i]);
                gameState.player3WallNo -= gameState.player3UsedWallNo;
                gameState.player4WallNo -= gameState.player4UsedWallNo;
                gameState.player3UsedWallNo = 0;
                gameState.player4UsedWallNo = 0;
            }
            break;
        case decreaseWallNo:
            indx = rand() % 3;
            if(gameState.turnSw == 0) {
                gameState.player1WallNo -= value[indx];
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
            }
            else if (gameState.turnSw == 1) {
                gameState.player2WallNo -= value[indx];
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
            }
            else if (gameState.turnSw == 2) {
                gameState.player3WallNo -= value[indx];
                gameState.player3WallNo = fmax(gameState.player3UsedWallNo, gameState.player3WallNo);
            }
            else {
                gameState.player4WallNo -= value[indx];
                gameState.player4WallNo = fmax(gameState.player4UsedWallNo, gameState.player4WallNo);
            }
            break;
        case blockTurn:
            specialValue = rand() % 2 + 1;
            gameState.playerBlockCount[gameState.turnSw] += specialValue;
            break;
        case increaseWallNo:
            indx = rand() % 3;
            if(gameState.turnSw == 0)
                gameState.player1WallNo += value[indx];
            else if(gameState.turnSw == 1)
                gameState.player2WallNo += value[indx];
            else if(gameState.turnSw == 2)
                gameState.player3WallNo += value[indx];
            else
                gameState.player4WallNo += value[indx];
            break;
        case specialIncreaseWallNo:
            specialValue = rand() % 2 + 1;
            if (gameState.turnSw == 0) {
                gameState.player1WallNo += specialValue;
                gameState.player2WallNo -= specialValue;
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
                if (gameState.playerCount == 4) {
                    gameState.player3WallNo -= specialValue;
                    gameState.player3WallNo = fmax(gameState.player3UsedWallNo, gameState.player3WallNo);
                    gameState.player4WallNo -= specialValue;
                    gameState.player4WallNo = fmax(gameState.player4UsedWallNo, gameState.player4WallNo);
                }
            }
            else if (gameState.turnSw == 1){
                gameState.player2WallNo += specialValue;
                gameState.player1WallNo -= specialValue;
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
                if (gameState.playerCount == 4) {
                    gameState.player3WallNo -= specialValue;
                    gameState.player3WallNo = fmax(gameState.player3UsedWallNo, gameState.player3WallNo);
                    gameState.player4WallNo -= specialValue;
                    gameState.player4WallNo = fmax(gameState.player4UsedWallNo, gameState.player4WallNo);
                }
            }
            else if (gameState.turnSw == 2) {
                gameState.player3WallNo += specialValue;
                gameState.player1WallNo -= specialValue;
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
                gameState.player2WallNo -= specialValue;
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
                gameState.player4WallNo -= specialValue;
                gameState.player4WallNo = fmax(gameState.player4UsedWallNo, gameState.player4WallNo);
            }
            else {
                gameState.player4WallNo += specialValue;
                gameState.player1WallNo -= specialValue;
                gameState.player1WallNo = fmax(gameState.player1UsedWallNo, gameState.player1WallNo);
                gameState.player2WallNo -= specialValue;
                gameState.player2WallNo = fmax(gameState.player2UsedWallNo, gameState.player2WallNo);
                gameState.player3WallNo -= specialValue;
                gameState.player3WallNo = fmax(gameState.player3UsedWallNo, gameState.player3WallNo);
            }
            break;
    }
}
