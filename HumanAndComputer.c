int invalidInput = 0;
int nextMove, moveSw = 0;

typedef enum gameScreen {starting = 0, game, ending} gameScreen;

Vector2 wallStartPoint = {50, 100};
Vector2 wallEndPoint = {50, 100};


void drawInvalid() {
    SetTargetFPS(2);
    Rectangle textBoxSize = {300, 425, 200, 50};
    DrawRectangleRec(textBoxSize, ColorAlpha(MAROON, 0.8));
    DrawText("Invalid Input!", textBoxSize.x + 22, textBoxSize.y + 12, 25, WHITE);

}

void drawBoard(int PlayerSize) {

    BeginDrawing();

    if (gameState.turnSw == 0)
        DrawText(TextFormat("%s's Turn To Move,", gameState.player1Name), 7, 5, 25, ColorAlpha(MAROON, 0.3));
    else if (gameState.turnSw == 1)
        DrawText(TextFormat("%s's Turn To Move,", gameState.player2Name), 7, 5, 25, ColorAlpha(DARKGREEN, 0.3));
    else if (gameState.turnSw == 2)
        DrawText(TextFormat("%s's Turn To Move,", gameState.player3Name), 7, 5, 25, ColorAlpha(ORANGE, 0.3));
    else
        DrawText(TextFormat("%s's Turn To Move,", gameState.player4Name), 7, 5, 25, ColorAlpha(DARKBLUE, 0.3));

    DrawText("The Arrow Keys In This Game Are w,d,s,a (Lowercase Or Uppercase). You May Use Them To Move Your \nPiece."
             "If You Wish To Place a wall, Press 'space'."
             " - Wall Movements Guide :\n"
             "Press The Mentioned Arrow Keys To Reach Your Intended Location. Press 'x' Or 'X' To Rotate The Wall.\n"
             "Press 'space' To Switch Moves, And 'l' Or 'L' Confirm Your Wall's Position.",
             5, 33, 13, ColorAlpha(GRAY, 0.7));

    DrawText("Remaining \nWalls :", 730, 7, 10, ColorAlpha(GRAY, 0.7));
    DrawText(TextFormat("%d", gameState.player1WallNo - gameState.player1UsedWallNo), 760, 40, 20, ColorAlpha(MAROON, 0.3));
    DrawText(TextFormat("%d", gameState.player2WallNo - gameState.player2UsedWallNo), 760, 62, 20, ColorAlpha(DARKGREEN, 0.3));
    if (gameState.playerCount == 4) {
        DrawText(TextFormat("%d", gameState.player3WallNo - gameState.player3UsedWallNo), 760, 84, 20,
                 ColorAlpha(ORANGE, 0.3));
        DrawText(TextFormat("%d", gameState.player4WallNo - gameState.player4UsedWallNo), 760, 106, 20,
                 ColorAlpha(DARKBLUE, 0.3));
    }
    Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2 + 50, gameState.player1Pos.y * PlayerSize + PlayerSize / 2 + 100};
    Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2 + 50, gameState.player2Pos.y * PlayerSize + PlayerSize / 2 + 100};
    Vector2 Player3 = {gameState.player3Pos.x * PlayerSize + PlayerSize / 2 + 50,gameState.player3Pos.y * PlayerSize + PlayerSize / 2 + 100};
    Vector2 Player4 = {gameState.player4Pos.x * PlayerSize + PlayerSize / 2 + 50,gameState.player4Pos.y * PlayerSize + PlayerSize / 2 + 100};

    ClearBackground(RAYWHITE);

    // Print Board :
    Rectangle boardCell = {50, 100, PlayerSize, PlayerSize};

    for (int i = 0; i < gameState.size; i++) {
        boardCell.x = 50;
        for (int j = 0; j < gameState.size; j++) {
            DrawRectangleLinesEx(boardCell, 1, LIGHTGRAY);
            if (gameState.talismans[j][i])
                DrawRectangleLinesEx(boardCell, 10, ColorAlpha(PURPLE, 0.2));
            boardCell.x += PlayerSize;
        }
        boardCell.y += PlayerSize;
    }

    // Print Players :
    DrawCircleV(Player1, 5 * PlayerSize / 12, ColorAlpha(MAROON, 0.3));
    DrawCircleV(Player2, 5 * PlayerSize / 12, ColorAlpha(DARKGREEN, 0.3));
    if (gameState.playerCount == 4) {
        DrawCircleV(Player3, 5 * PlayerSize / 12, ColorAlpha(ORANGE, 0.3));
        DrawCircleV(Player4, 5 * PlayerSize / 12, ColorAlpha(DARKBLUE, 0.3));
    }

    // Print Player 1 walls :
    for (int i = 0; i < gameState.player1UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player1WallList[i].x * PlayerSize + 50, gameState.player1WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player1WallList[i].dir == 'V' || gameState.player1WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    //Print Player 2 walls :
    for (int i = 0; i < gameState.player2UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player2WallList[i].x * PlayerSize + 50, gameState.player2WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player2WallList[i].dir == 'V' || gameState.player2WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    // Print Player 3 walls :
    for (int i = 0; i < gameState.player3UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player3WallList[i].x * PlayerSize + 50, gameState.player3WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player3WallList[i].dir == 'V' || gameState.player3WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    // Print Player 4 walls :
    for (int i = 0; i < gameState.player4UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player4WallList[i].x * PlayerSize + 50, gameState.player4WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player4WallList[i].dir == 'V' || gameState.player4WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(BLUE, 0.2));

    if (invalidInput)
        drawInvalid();

    EndDrawing();
}

void drawEnding(int winner) {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.5));

    if (winner == 1)
        DrawText(TextFormat("%s Won!", gameState.player1Name), 220, 400, 50, WHITE);
    else if (winner == 2)
        DrawText(TextFormat("%s Won!", gameState.player2Name), 220, 400, 50, WHITE);
    else if (winner == 3)
        DrawText(TextFormat("%s Won!", gameState.player3Name), 220, 400, 50, WHITE);
    else
        DrawText(TextFormat("%s Won!", gameState.player4Name), 220, 400, 50, WHITE);

    EndDrawing();
}

void drawStarting() {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

    DrawText("Use  'L'  to confirm your input and  'E'  to erase it.", 20, 120, 20, ColorAlpha(GRAY, 1));

    DrawText("Please Enter The Size Of Your Board :", 20, 220, 25, WHITE);

    Rectangle textBoxSize = {525, 218, 50, 30};
    DrawRectangleRec(textBoxSize, WHITE);

    if (!size.isSet) {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));

        if (size.validLengthEx)
            DrawText("The Size Of The Board Should Be Less Than 100 Units!", 155, 260, 18, ColorAlpha(MAROON, 0.5));
    }
    else {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));

        DrawText("Please Enter The Number Of Walls For Each Player :", 20, 300, 25, WHITE);
        Rectangle textBoxWallNo = {700, 298, 50, 30};
        DrawRectangleRec(textBoxWallNo, WHITE);

        if (!wallNo.isSet) {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));

            if (wallNo.validLengthEx)
                DrawText("The Size Of The Board Should Be Less Than 100 Units!", 300, 340, 18, ColorAlpha(MAROON, 0.5));

        }
        else {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));

            DrawText("Please Enter First Player's Name :", 20, 380, 25, WHITE);
            Rectangle textBoxPlayer1Name = {462, 378, 130, 30};
            DrawRectangleRec(textBoxPlayer1Name, WHITE);

            if (!player1Name.isSet) {
                DrawText(player1Name.value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                DrawText("Player's Name Should Only Contain Lowercase English Letters!", 100, 420, 18, ColorAlpha(DARKGREEN, 0.3));

                if (player1Name.validLengthEx)
                    DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 100, 460, 18, ColorAlpha(MAROON, 0.5));
            }
            else {
                DrawText(player1Name.value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(GRAY, 0.7));

                DrawText("Please Enter Second Player's Name :", 20, 460, 25, WHITE);
                Rectangle textBoxPlayer2Name = {490, 458, 130, 30};
                DrawRectangleRec(textBoxPlayer2Name, WHITE);

                if (!player2Name.isSet ) {
                    DrawText(player2Name.value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                    DrawText("Player's Name Should Only Contain Lowercase English Letters!!", 115, 500, 18, ColorAlpha(DARKGREEN, 0.3));

                    if (player2Name.validLengthEx)
                        DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 115, 540, 18, ColorAlpha(MAROON, 0.5));
                }
                else if (gameState.playerCount == 4) {
                    DrawText(player2Name.value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20,
                             ColorAlpha(GRAY, 0.7));

                    DrawText("Please Enter Third Player's Name :", 20, 540, 25, WHITE);
                    Rectangle textBoxPlayer3Name = {490, 538, 130, 30};
                    DrawRectangleRec(textBoxPlayer3Name, WHITE);

                    if (!player3Name.isSet ) {
                        DrawText(player3Name.value, (int) textBoxPlayer3Name.x + 13, (int) textBoxPlayer3Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                        DrawText("Player's Name Should Only Contain Lowercase English Letters!!", 115, 580, 18, ColorAlpha(DARKGREEN, 0.3));

                        if (player3Name.validLengthEx)
                            DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 115, 620, 18, ColorAlpha(MAROON, 0.5));
                    }
                    else {
                        DrawText(player3Name.value, (int) textBoxPlayer3Name.x + 13, (int) textBoxPlayer3Name.y + 7, 20,
                                 ColorAlpha(GRAY, 0.7));

                        DrawText("Please Enter Fourth Player's Name :", 20, 620, 25, WHITE);
                        Rectangle textBoxPlayer4Name = {490, 618, 130, 30};
                        DrawRectangleRec(textBoxPlayer4Name, WHITE);

                        if (!player4Name.isSet ) {
                            DrawText(player4Name.value, (int) textBoxPlayer4Name.x + 13, (int) textBoxPlayer4Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                            DrawText("Player's Name Should Only Contain Lowercase English Letters!!", 115, 660, 18, ColorAlpha(DARKGREEN, 0.3));

                            if (player4Name.validLengthEx)
                                DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 115, 700, 18, ColorAlpha(MAROON, 0.5));
                        }
                        else {
                            DrawText(player4Name.value, (int) textBoxPlayer4Name.x + 13, (int) textBoxPlayer4Name.y + 7, 20,
                                     ColorAlpha(GRAY, 0.7));

                            DrawText("Press 'L' To Begin!", 115, 750, 20, ColorAlpha(GRAY, 1));
                        }
                    }


                }
                else {
                    DrawText(player2Name.value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20,
                             ColorAlpha(GRAY, 0.7));

                    DrawText("Press 'L' To Begin!", 115, 750, 20, ColorAlpha(GRAY, 1));
                }
            }
        }
    }

    EndDrawing();
}

void nextMoveProcess(struct position *player) {

    switch (nextMove) {
        case 'W':
        case 'w':
            if (! wallForEachCell[(*player).x][(*player).y][0]) {
                (*player).y--;
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
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
            else
                invalidInput = 1;
            break;
        case 'S':
        case 's':
            if (! wallForEachCell[(*player).x][(*player).y][2]) {
                (*player).y++;
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
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
            else
                invalidInput = 1;
            break;
        case 'A':
        case 'a':
            if (! wallForEachCell[(*player).x][(*player).y][3]) {
                (*player).x--;
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
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
            else
                invalidInput = 1;
            break;
        case 'D':
        case 'd':
            if (! wallForEachCell[(*player).x][(*player).y][1]) {
                (*player).x++;
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
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
            else
                invalidInput = 1;
            break;
    }

}

void setWallPos(int PlayerSize) {

    wallStartPoint.y += (gameState.size / 2) * PlayerSize;
    wallEndPoint.x += PlayerSize * 2;
    wallEndPoint.y += (gameState.size / 2) * PlayerSize;

    while (1) {

        nextMove = GetCharPressed();

        if (invalidInput) {
            invalidInput = 0;
            SetTargetFPS(10);
        }

        switch (nextMove) {
            case 'W':
            case 'w':
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y - PlayerSize, wallEndPoint.x))
                    wallStartPoint.y -= PlayerSize, wallEndPoint.y -= PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'S':
            case 's':
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y + PlayerSize, wallEndPoint.x))
                    wallStartPoint.y += PlayerSize, wallEndPoint.y += PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'D':
            case 'd':
                if (wallCanGo(PlayerSize, wallStartPoint.x + PlayerSize, wallStartPoint.y, wallEndPoint.x + PlayerSize))
                    wallStartPoint.x += PlayerSize, wallEndPoint.x += PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'A':
            case 'a':
                if (wallCanGo(PlayerSize, wallStartPoint.x - PlayerSize, wallStartPoint.y, wallEndPoint.x - PlayerSize))
                    wallStartPoint.x -= PlayerSize, wallEndPoint.x -= PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'X':
            case 'x':
                if (wallStartPoint.x != wallEndPoint.x) wallStartPoint.x += PlayerSize, wallStartPoint.y -= PlayerSize, wallEndPoint.x -= PlayerSize, wallEndPoint.y += PlayerSize;
                else wallStartPoint.x -= PlayerSize, wallStartPoint.y += PlayerSize, wallEndPoint.x += PlayerSize, wallEndPoint.y -= PlayerSize;
                break;
            case ' ':
                moveSw = 1;
                return;
        }

        if (nextMove == 'l' || nextMove == 'L') {

            struct wall newWall;

            newWall.x = (wallStartPoint.x - 50) / PlayerSize;
            newWall.y = (wallStartPoint.y - 100) / PlayerSize;

            if (wallStartPoint.x != wallEndPoint.x)
                newWall.dir = 'h';
            else
                newWall.dir = 'v';

            if (validWall(newWall))
                break;
            else
                invalidInput = 1;
        }

        drawBoard(PlayerSize);

    }
}

int whoWins() {
    if (gameState.player1Pos.y == gameState.size - 1)
        return 1;
    if (!gameState.player2Pos.y)
        return 2;
    if (gameState.playerCount == 4) {
        if (gameState.player3Pos.x == gameState.size - 1)
            return 3;
        if (!gameState.player4Pos.x)
            return 4;
    }
    return 0;
}

void getString(struct stringInStartingScreen *s) {

    // Write and save string while the player is typing
    while (nextMove > 0) {

        if (nextMove == 'L'&& (*s).realLength) (*s).isSet = 1;

        else if (nextMove >= (*s).validValueS && nextMove <= (*s).validValueE && (*s).realLength < (*s).validLength) {
            (*s).value[(*s).realLength] = (char) nextMove;
            (*s).value[(*s).realLength + 1] = '\0';
            (*s).realLength++;
        }

        else if (nextMove == 'E') {
            (*s).realLength--;
            if ((*s).realLength < 0) (*s).realLength = 0;
            (*s).value[(*s).realLength] = '\0';
            if ((*s).validLengthEx) (*s).validLengthEx = 0;
        }

        else if ((*s).realLength == (*s).validLength)
            (*s).validLengthEx = 1;

        nextMove = GetCharPressed();
    }
}