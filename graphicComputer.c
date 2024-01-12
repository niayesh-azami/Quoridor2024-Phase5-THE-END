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
                            if (gameState.player2Type && !player2Name.isSet) {
                                strcpy(player2Name.value, "Mr. Jabal");
                                player2Name.isSet = 1;
                            }
                            else if (!player2Name.isSet)
                                getString(&player2Name);
                            else if (gameState.playerCount == 4){
                                if (gameState.player3Type && !player3Name.isSet) {
                                    strcpy(player3Name.value, "Mr. Jabal2");
                                    player3Name.isSet = 1;
                                }
                                else if (!player3Name.isSet)
                                    getString(&player3Name);
                                else {
                                    if (gameState.player4Type && !player4Name.isSet) {
                                        strcpy(player4Name.value, "Mr. Jabal3");
                                        player4Name.isSet = 1;
                                    }
                                    else if (!player4Name.isSet)
                                        getString(&player4Name);
                                    else {
                                        getStarted(size, wallNo, player1Name, player2Name);

                                        // Starting The Real Game :
                                        if (nextMove == 'L')
                                            currentScreen = game;
                                    }
                                }
                            }
                            else {
                                getStarted(size, wallNo, player1Name, player2Name);

                                // Starting The Real Game :
                                if (nextMove == 'L')
                                    currentScreen = game;
                            }

                        }
                    }
                }
                drawStarting();
                break;

            case game:

                PlayerSize = (screenWidth - 100) / gameState.size;
                if (!whoWins()) {

                    if (gameState.turnSw == 0) {
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

                                    int i = (gameState.turnSw + 1) % gameState.playerCount;
                                    while (1) {
                                        if (!gameState.playerBlockCount[i]) {
                                            gameState.turnSw = i;
                                            break;
                                        }
                                        gameState.playerBlockCount[i]--;
                                        i = (i + 1) % gameState.playerCount;
                                    }

                                } else
                                    moveSw = 0;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                            }
                        } else
                            nextMoveProcess(&gameState.player1Pos);
                    }
                    else if (gameState.turnSw == 1) {

                        if (gameState.player2Type) {
                            minimax(true, 4, -inF, inF, gameState.turnSw);

                            if (computerMove.type == 'p') {
                                gameState.player2Pos = computerMove.playerPos;
                                if (gameState.talismans[gameState.player2Pos.x][gameState.player2Pos.y]) {
                                    applyTalisman();
                                    gameState.talismans[gameState.player2Pos.x][gameState.player2Pos.y] = 0;
                                }
                            } else {
                                blockCell(computerMove.wallPos);
                                gameState.player2WallList[gameState.player2UsedWallNo] = computerMove.wallPos;
                                gameState.player2UsedWallNo++;
                            }

                            int i = (gameState.turnSw + 1) % gameState.playerCount;
                            while (1) {
                                if (!gameState.playerBlockCount[i]) {
                                    gameState.turnSw = i;
                                    break;
                                }
                                gameState.playerBlockCount[i]--;
                                i = (i + 1) % gameState.playerCount;
                            }
                        }
                        else {
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

                            if (nextMove == ' ') {
                                if (gameState.player2UsedWallNo >= gameState.player2WallNo) {
                                    invalidInput = 1;
                                } else {
                                    setWallPos(PlayerSize);

                                    if (!moveSw) {
                                        gameState.player2WallList[gameState.player2UsedWallNo].x =
                                                (wallStartPoint.x - 50) / PlayerSize;
                                        gameState.player2WallList[gameState.player2UsedWallNo].y =
                                                (wallStartPoint.y - 100) / PlayerSize;

                                        if (wallStartPoint.x != wallEndPoint.x)
                                            gameState.player2WallList[gameState.player2UsedWallNo].dir = 'h';
                                        else gameState.player2WallList[gameState.player2UsedWallNo].dir = 'v';

                                        blockCell(gameState.player2WallList[gameState.player2UsedWallNo]);

                                        gameState.player2UsedWallNo++;

                                        int i = (gameState.turnSw + 1) % gameState.playerCount;
                                        while (1) {
                                            if (!gameState.playerBlockCount[i]) {
                                                gameState.turnSw = i;
                                                break;
                                            }
                                            gameState.playerBlockCount[i]--;
                                            i = (i + 1) % gameState.playerCount;
                                        }

                                    } else
                                        moveSw = 0;

                                    wallStartPoint.x = 50, wallStartPoint.y = 100;
                                    wallEndPoint.x = 50, wallEndPoint.y = 100;

                                }
                            } else
                                nextMoveProcess(&gameState.player2Pos);
                        }
                    }
                    else if (gameState.turnSw == 2) {

                        if (gameState.player3Type) {
                            minimax(true, 4, -inF, inF, gameState.turnSw);

                            if (computerMove.type == 'p') {
                                gameState.player3Pos = computerMove.playerPos;
                                if (gameState.talismans[gameState.player3Pos.x][gameState.player3Pos.y]) {
                                    applyTalisman();
                                    gameState.talismans[gameState.player3Pos.x][gameState.player3Pos.y] = 0;
                                }
                            } else {
                                blockCell(computerMove.wallPos);
                                gameState.player3WallList[gameState.player3UsedWallNo] = computerMove.wallPos;
                                gameState.player3UsedWallNo++;
                            }

                            int i = (gameState.turnSw + 1) % 4;
                            while (1) {
                                if (!gameState.playerBlockCount[i]) {
                                    gameState.turnSw = i;
                                    break;
                                }
                                gameState.playerBlockCount[i]--;
                                i = (i + 1) % 4;
                            }
                        }
                        else {
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

                            if (nextMove == ' ') {
                                if (gameState.player3UsedWallNo >= gameState.player3WallNo) {
                                    invalidInput = 1;
                                } else {
                                    setWallPos(PlayerSize);

                                    if (!moveSw) {
                                        gameState.player3WallList[gameState.player3UsedWallNo].x =
                                                (wallStartPoint.x - 50) / PlayerSize;
                                        gameState.player3WallList[gameState.player3UsedWallNo].y =
                                                (wallStartPoint.y - 100) / PlayerSize;

                                        if (wallStartPoint.x != wallEndPoint.x)
                                            gameState.player3WallList[gameState.player3UsedWallNo].dir = 'h';
                                        else gameState.player3WallList[gameState.player3UsedWallNo].dir = 'v';

                                        blockCell(gameState.player3WallList[gameState.player3UsedWallNo]);

                                        gameState.player3UsedWallNo++;

                                        int i = (gameState.turnSw + 1) % 4;
                                        while (1) {
                                            if (!gameState.playerBlockCount[i]) {
                                                gameState.turnSw = i;
                                                break;
                                            }
                                            gameState.playerBlockCount[i]--;
                                            i = (i + 1) % 4;
                                        }

                                    } else
                                        moveSw = 0;

                                    wallStartPoint.x = 50, wallStartPoint.y = 100;
                                    wallEndPoint.x = 50, wallEndPoint.y = 100;

                                }
                            } else
                                nextMoveProcess(&gameState.player3Pos);
                        }
                    }
                    else {

                        if (gameState.player4Type) {
                            minimax(true, 4, -inF, inF, gameState.turnSw);

                            if (computerMove.type == 'p') {
                                gameState.player4Pos = computerMove.playerPos;
                                if (gameState.talismans[gameState.player4Pos.x][gameState.player4Pos.y]) {
                                    applyTalisman();
                                    gameState.talismans[gameState.player4Pos.x][gameState.player4Pos.y] = 0;
                                }
                            } else {
                                blockCell(computerMove.wallPos);
                                gameState.player4WallList[gameState.player4UsedWallNo] = computerMove.wallPos;
                                gameState.player4UsedWallNo++;
                            }

                            int i = (gameState.turnSw + 1) % 4;
                            while (1) {
                                if (!gameState.playerBlockCount[i]) {
                                    gameState.turnSw = i;
                                    break;
                                }
                                gameState.playerBlockCount[i]--;
                                i = (i + 1) % 4;
                            }
                        }
                        else {
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

                            if (nextMove == ' ') {
                                if (gameState.player4UsedWallNo >= gameState.player4WallNo) {
                                    invalidInput = 1;
                                } else {
                                    setWallPos(PlayerSize);

                                    if (!moveSw) {
                                        gameState.player4WallList[gameState.player4UsedWallNo].x =
                                                (wallStartPoint.x - 50) / PlayerSize;
                                        gameState.player4WallList[gameState.player4UsedWallNo].y =
                                                (wallStartPoint.y - 100) / PlayerSize;

                                        if (wallStartPoint.x != wallEndPoint.x)
                                            gameState.player4WallList[gameState.player4UsedWallNo].dir = 'h';
                                        else gameState.player4WallList[gameState.player4UsedWallNo].dir = 'v';

                                        blockCell(gameState.player4WallList[gameState.player4UsedWallNo]);

                                        gameState.player4UsedWallNo++;

                                        int i = (gameState.turnSw + 1) % 4;
                                        while (1) {
                                            if (!gameState.playerBlockCount[i]) {
                                                gameState.turnSw = i;
                                                break;
                                            }
                                            gameState.playerBlockCount[i]--;
                                            i = (i + 1) % 4;
                                        }

                                    } else
                                        moveSw = 0;

                                    wallStartPoint.x = 50, wallStartPoint.y = 100;
                                    wallEndPoint.x = 50, wallEndPoint.y = 100;

                                }
                            } else
                                nextMoveProcess(&gameState.player4Pos);
                        }
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