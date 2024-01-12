void graphicComputer() {

    // DrawScreen Related Values :
    int PlayerSize;
    int screenWidth = 800;
    int screenHeight = 810;

    // Setting Input Data To Null Before Reading Them :
    getReadyToRead();

    // Set Default Screen To The Starting Screen :
    gameScreen currentScreen = newGame? starting: game;

    InitWindow(screenWidth, screenHeight, "Quoridor");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // Update Data And Draw Screen:
        switch (currentScreen) {
            case starting:
                nextMove = GetCharPressed();

                // Read and Save Board Size, Number Of Walls For Each Player And Their Names :
                if (!size.isSet) //User Is Not Done Typing Board Size.
                    getString(&size);
                else { // User Is Done Typing Board Size And Will Now Start Typing The Number Of Walls For Each Player.
                    if (!wallNo.isSet)
                        getString(&wallNo);
                    else {
                        if (!player1Name.isSet)
                            getString(&player1Name);
                        else {
                            strcpy(player2Name.value, "Mr. Jabal");
                            player2Name.isSet = 1;

                            getStarted(size, wallNo, player1Name, player2Name);

                            // Starting The Real Game :
                            if (nextMove == 'L')
                                currentScreen = game;
                        }
                    }
                }
                drawStarting();
                break;

            case game:

                PlayerSize = (screenWidth - 100) / gameState.size;

                if (!whoWins()) {
                    if (! gameState.turnSw)
                        nextMove = GetCharPressed();

                    if (nextMove == 'q' || nextMove == 'Q') {
                        FILE *outFile;
                        outFile = fopen("gameState.dat", "wb");
                        if (!outFile) {
                            printf("could Not open file\n");
                            exit(0);
                        }
                        fwrite(&gameState, sizeof(gameState), 1, outFile);
                        fclose(outFile);
                        exit(0);
                    }

                    if (invalidInput) {
                        invalidInput = 0;
                        SetTargetFPS(10);
                    }

                    if (!gameState.turnSw) {
                        if (nextMove == ' ') {
                            if (gameState.player1UsedWallNo >= gameState.player1WallNo) {
                                invalidInput = 1;
                            } else {
                                setWallPos(PlayerSize);

                                if (!moveSw) {
                                    gameState.player1WallList[gameState.player1UsedWallNo].x =
                                            (wallStartPoint.x - 50) / PlayerSize;
                                    gameState.player1WallList[gameState.player1UsedWallNo].y =
                                            (wallStartPoint.y - 100) / PlayerSize;

                                    if (wallStartPoint.x != wallEndPoint.x)
                                        gameState.player1WallList[gameState.player1UsedWallNo].dir = 'h';
                                    else gameState.player1WallList[gameState.player1UsedWallNo].dir = 'v';

                                    blockCell(gameState.player1WallList[gameState.player1UsedWallNo]);

                                    gameState.player1UsedWallNo++;
                                    if (!gameState.player2BlockCount)
                                        gameState.turnSw = 1;
                                    else
                                        gameState.player2BlockCount--;
                                } else
                                    moveSw = 0;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                            }
                        } else
                            nextMoveProcess(&gameState.player1Pos);
                    }
                    else {

                        minimax(true, 4, -inF, inF, true);

                        sleep(1.5);

                        if (computerMove.type == 'p') {
                            gameState.player2Pos = computerMove.playerPos;
                            gameState.turnSw ^= 1;
                            if (gameState.talismans[gameState.player2Pos.x][gameState.player2Pos.y]) {
                                applyTalisman();
                                gameState.talismans[gameState.player2Pos.x][gameState.player2Pos.y] = 0;
                            }
                            gameState.turnSw ^= 1;
                        }
                        else {
                            blockCell(computerMove.wallPos);
                            gameState.player2WallList[gameState.player2UsedWallNo] = computerMove.wallPos;
                            gameState.player2UsedWallNo++;
                        }
                        if (!gameState.player1BlockCount)
                            gameState.turnSw = 0;
                        else
                            gameState.player1BlockCount--;
                    }

                    drawBoard(PlayerSize);
                }
                else {
                    FILE *inFile;
                    inFile = fopen("gameState.dat", "wb");
                    fclose(inFile);
                    drawEnding(whoWins());
                }
                break;
        }

    }

    CloseWindow();

}