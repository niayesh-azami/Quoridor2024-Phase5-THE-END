int  talismanIsSet = 0;
struct stringInStartingScreen size, wallNo, player1Name, player2Name, player3Name, player4Name;

void setWallaroundTheBoard() {

    // set walls around the board so the player's piece doesn't run away :
    memset(wallForEachCell, 0, sizeof wallForEachCell);

    for (int i = 0; i < gameState.size; i++) {
        wallForEachCell[i][0][0] = 1;
        wallForEachCell[i][gameState.size - 1][2] = 1;
        wallForEachCell[0][i][3] = 1;
        wallForEachCell[gameState.size - 1][i][1] = 1;
    }
}

void setNull(struct stringInStartingScreen *s) {
    (*s).realLength = 0, (*s).isSet = 0, (*s).validLengthEx = 0, (*s).value[0] = '\0';
}

void getReadyToRead() {

    setNull(&size); size.validLength = 2, size.validValueS = '0', size.validValueE = '9';
    setNull(&wallNo); wallNo.validLength = 2, wallNo.validValueS = '0', wallNo.validValueE = '9';
    setNull(&player1Name); player1Name.validLength = 10, player1Name.validValueS = 'a', player1Name.validValueE = 'z';
    setNull(&player2Name); player2Name.validLength = 10, player2Name.validValueS = 'a', player2Name.validValueE = 'z';
    setNull(&player3Name); player3Name.validLength = 10, player3Name.validValueS = 'a', player3Name.validValueE = 'z';
    setNull(&player4Name); player4Name.validLength = 10, player4Name.validValueS = 'a', player4Name.validValueE = 'z';

}

void getStarted(struct stringInStartingScreen size, struct stringInStartingScreen wallNo, struct stringInStartingScreen player1Name, struct stringInStartingScreen player2Name) {

    gameState.size = atoi(size.value);

    gameState.player1WallNo = atoi(wallNo.value);
    gameState.player2WallNo = atoi(wallNo.value);
    gameState.player3WallNo = atoi(wallNo.value);
    gameState.player4WallNo = atoi(wallNo.value);

    strcpy(gameState.player1Name, player1Name.value);
    strcpy(gameState.player2Name, player2Name.value);
    strcpy(gameState.player3Name, player3Name.value);
    strcpy(gameState.player4Name, player4Name.value);

    // set Players' Starting Positions :
    gameState.player1Pos.y = 0;
    gameState.player1Pos.x = gameState.size / 2;
    gameState.player2Pos.y = gameState.size - 1;
    gameState.player2Pos.x = gameState.size / 2;
    gameState.player3Pos.y = gameState.size / 2;
    gameState.player3Pos.x = 0;
    gameState.player4Pos.y = gameState.size / 2;
    gameState.player4Pos.x = gameState.size - 1;

    gameState.player1UsedWallNo = 0;
    gameState.player2UsedWallNo = 0;
    gameState.player3UsedWallNo = 0;
    gameState.player4UsedWallNo = 0;

    gameState.turnSw = 0;

    for (int i = 0; i < 4; i++)
    gameState.playerBlockCount[i] = 0;

    setWallaroundTheBoard();

    if (!talismanIsSet)
        generateTalismanPosition(), talismanIsSet = 1;
}
