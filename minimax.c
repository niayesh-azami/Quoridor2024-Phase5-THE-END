struct move computerMove;

double heuristic() {
    if (gameState.turnSw == 1) {
        aStarAlgorithm(1, gameState.player2Pos, 0);
        int minDisPlayer2 = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer2 = fmin(cellDetails[i][0].g, minDisPlayer2);

        aStarAlgorithm(0, gameState.player1Pos, gameState.size - 1);
        int minDisPlayer = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[i][gameState.size - 1].g, minDisPlayer);

        if (gameState.playerCount == 4) {
            aStarAlgorithm(2, gameState.player3Pos, gameState.size - 1);
            for (int i = 0; i < gameState.size; i++)
                minDisPlayer = fmin(cellDetails[gameState.size - 1][i].g, minDisPlayer);

            aStarAlgorithm(3, gameState.player4Pos, 0);
            for (int i = 0; i < gameState.size; i++)
                minDisPlayer = fmin(cellDetails[0][i].g, minDisPlayer);
        }
        return ((double) minDisPlayer - (double) minDisPlayer2);
    }


    if (gameState.turnSw == 2) {
        aStarAlgorithm(2, gameState.player3Pos, 0);
        int minDisPlayer3 = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer3 = fmin(cellDetails[gameState.size - 1][i].g, minDisPlayer3);

        aStarAlgorithm(0, gameState.player1Pos, gameState.size - 1);
        int minDisPlayer = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[i][gameState.size - 1].g, minDisPlayer);

        aStarAlgorithm(1, gameState.player2Pos, gameState.size - 1);
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[i][0].g, minDisPlayer);

        aStarAlgorithm(3, gameState.player4Pos, 0);
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[0][i].g, minDisPlayer);

        return ((double) minDisPlayer - (double) minDisPlayer3);
    }


    if (gameState.turnSw == 3) {
        aStarAlgorithm(3, gameState.player4Pos, 0);
        int minDisPlayer4 = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer4 = fmin(cellDetails[0][i].g, minDisPlayer4);

        aStarAlgorithm(0, gameState.player1Pos, gameState.size - 1);
        int minDisPlayer = inF;
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[i][gameState.size - 1].g, minDisPlayer);

        aStarAlgorithm(1, gameState.player2Pos, 0);
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[i][0].g, minDisPlayer);

        aStarAlgorithm(2, gameState.player3Pos, gameState.size - 1);
        for (int i = 0; i < gameState.size; i++)
            minDisPlayer = fmin(cellDetails[gameState.size - 1][i].g, minDisPlayer);

        return ((double) minDisPlayer - (double) minDisPlayer4);
    }
}

double minimax(int isRoot, int depth, int alpha, int beta, int turn) {
    if (whoWins() && whoWins() != gameState.turnSw + 1) return (depth + 1) * -inF;
    else if (whoWins() == gameState.turnSw + 1) return (depth + 1) * inF;
    if (!depth)
        return heuristic();

    if (turn == gameState.turnSw) {

        double maxEval = -6 * inF;

        int x, y;
        switch (gameState.turnSw) {
            case 1:
                x = gameState.player2Pos.x;
                y = gameState.player2Pos.y;
                break;
            case 2:
                x = gameState.player3Pos.x;
                y = gameState.player3Pos.y;
                break;
            case 3:
                x = gameState.player4Pos.x;
                y = gameState.player4Pos.y;
                break;
        }

        int Break = 0;

        if (!Break && !wallForEachCell[x][y][0]) {
            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.y -= 1;
                    break;
                case 2:
                    gameState.player3Pos.y -= 1;
                    break;
                case 3:
                    gameState.player4Pos.y -= 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';

                    switch (gameState.turnSw) {
                        case 1:
                            computerMove.playerPos = gameState.player2Pos;
                            break;
                        case 2:
                            computerMove.playerPos = gameState.player3Pos;
                            break;
                        case 3:
                            computerMove.playerPos = gameState.player4Pos;
                            break;
                    }
                }
            }

            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.y += 1;
                    break;
                case 2:
                    gameState.player3Pos.y += 1;
                    break;
                case 3:
                    gameState.player4Pos.y += 1;
                    break;
            }

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][1]) {
            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.x += 1;
                    break;
                case 2:
                    gameState.player3Pos.x += 1;
                    break;
                case 3:
                    gameState.player4Pos.x += 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';

                    switch (gameState.turnSw) {
                        case 1:
                            computerMove.playerPos = gameState.player2Pos;
                            break;
                        case 2:
                            computerMove.playerPos = gameState.player3Pos;
                            break;
                        case 3:
                            computerMove.playerPos = gameState.player4Pos;
                            break;
                    }
                }
            }

            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.x -= 1;
                    break;
                case 2:
                    gameState.player3Pos.x -= 1;
                    break;
                case 3:
                    gameState.player4Pos.x -= 1;
                    break;
            }

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][2]) {
            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.y += 1;
                    break;
                case 2:
                    gameState.player3Pos.y += 1;
                    break;
                case 3:
                    gameState.player4Pos.y += 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    switch (gameState.turnSw) {
                        case 1:
                            computerMove.playerPos = gameState.player2Pos;
                            break;
                        case 2:
                            computerMove.playerPos = gameState.player3Pos;
                            break;
                        case 3:
                            computerMove.playerPos = gameState.player4Pos;
                            break;
                    }
                }
            }

            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.y -= 1;
                    break;
                case 2:
                    gameState.player3Pos.y -= 1;
                    break;
                case 3:
                    gameState.player4Pos.y -= 1;
                    break;
            }

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][3]) {
            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.x -= 1;
                    break;
                case 2:
                    gameState.player3Pos.x -= 1;
                    break;
                case 3:
                    gameState.player4Pos.x -= 1;
                    break;
            }
            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    switch (gameState.turnSw) {
                        case 1:
                            computerMove.playerPos = gameState.player2Pos;
                            break;
                        case 2:
                            computerMove.playerPos = gameState.player3Pos;
                            break;
                        case 3:
                            computerMove.playerPos = gameState.player4Pos;
                            break;
                    }
                }
            }

            switch (gameState.turnSw) {
                case 1:
                    gameState.player2Pos.x += 1;
                    break;
                case 2:
                    gameState.player3Pos.x += 1;
                    break;
                case 3:
                    gameState.player4Pos.x += 1;
                    break;
            }

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        switch (gameState.turnSw) {
            case 1:
                if (gameState.player2UsedWallNo >= gameState.player2WallNo) Break = 1;
                break;
            case 2:
                if (gameState.player3UsedWallNo >= gameState.player3WallNo) Break = 1;
                break;
            case 3:
                if (gameState.player4UsedWallNo >= gameState.player4WallNo) Break = 1;
                break;
        }

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'h';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    switch (gameState.turnSw) {
                        case 1:
                            gameState.player2UsedWallNo++;
                            break;
                        case 2:
                            gameState.player3UsedWallNo++;
                            break;
                        case 3:
                            gameState.player4UsedWallNo++;
                            break;
                    }

                    double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    unBlockCell(newWall);
                    switch (gameState.turnSw) {
                        case 1:
                            gameState.player2UsedWallNo--;
                            break;
                        case 2:
                            gameState.player3UsedWallNo--;
                            break;
                        case 3:
                            gameState.player4UsedWallNo--;
                            break;
                    }

                    if (eval > maxEval) {
                        maxEval = eval;
                        if (isRoot) {
                            computerMove.type = 'w';
                            computerMove.wallPos.dir = 'h';
                            computerMove.wallPos.x = newWall.x;
                            computerMove.wallPos.y = newWall.y;
                        }
                    }

                    alpha = fmax(alpha, eval);
                    if (beta <= alpha)
                        Break = 1;
                }
            }

        for (int wallX = 1; !Break && wallX < gameState.size; wallX++)
            for (int wallY = 0; !Break && wallY < gameState.size - 1; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'v';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    switch (gameState.turnSw) {
                        case 1:
                            gameState.player2UsedWallNo++;
                            break;
                        case 2:
                            gameState.player3UsedWallNo++;
                            break;
                        case 3:
                            gameState.player4UsedWallNo++;
                            break;
                    }
                    double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    unBlockCell(newWall);
                    switch (gameState.turnSw) {
                        case 1:
                            gameState.player2UsedWallNo--;
                            break;
                        case 2:
                            gameState.player3UsedWallNo--;
                            break;
                        case 3:
                            gameState.player4UsedWallNo--;
                            break;
                    }

                    if (eval > maxEval) {
                        maxEval = eval;
                        if (isRoot) {
                            computerMove.type = 'w';
                            computerMove.wallPos.dir = 'v';
                            computerMove.wallPos.x = newWall.x;
                            computerMove.wallPos.y = newWall.y;
                        }
                    }

                    alpha = fmax(alpha, eval);
                    if (beta <= alpha)
                        Break = 1;
                }
            }
        return maxEval;
    }
    else {

        double minEval = 6 * inF;

        int x, y;
        switch (turn) {
            case 0:
                x = gameState.player1Pos.x;
                y = gameState.player1Pos.y;
                break;
            case 1:
                x = gameState.player2Pos.x;
                y = gameState.player2Pos.y;
                break;
            case 2:
                x = gameState.player3Pos.x;
                y = gameState.player3Pos.y;
                break;
            case 3:
                x = gameState.player4Pos.x;
                y = gameState.player4Pos.y;
                break;
        }

        int Break = 0;

        if (!Break && !wallForEachCell[x][y][0]) {
            switch (turn) {
                case 0:
                    gameState.player1Pos.y -= 1;
                    break;
                case 1:
                    gameState.player2Pos.y -= 1;
                    break;
                case 2:
                    gameState.player3Pos.y -= 1;
                    break;
                case 3:
                    gameState.player4Pos.y -= 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval)
                minEval = eval;


            switch (turn) {
                case 0:
                    gameState.player1Pos.y += 1;
                    break;
                case 1:
                    gameState.player2Pos.y += 1;
                    break;
                case 2:
                    gameState.player3Pos.y += 1;
                    break;
                case 3:
                    gameState.player4Pos.y += 1;
                    break;
            }

            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][1]) {
            switch (turn) {
                case 0:
                    gameState.player1Pos.x += 1;
                    break;
                case 1:
                    gameState.player2Pos.x += 1;
                    break;
                case 2:
                    gameState.player3Pos.x += 1;
                    break;
                case 3:
                    gameState.player4Pos.x += 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval)
                minEval = eval;

            switch (turn) {
                case 0:
                    gameState.player1Pos.x -= 1;
                    break;
                case 1:
                    gameState.player2Pos.x -= 1;
                    break;
                case 2:
                    gameState.player3Pos.x -= 1;
                    break;
                case 3:
                    gameState.player4Pos.x -= 1;
                    break;
            }

            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][2]) {
            switch (turn) {
                case 0:
                    gameState.player1Pos.y += 1;
                    break;
                case 1:
                    gameState.player2Pos.y += 1;
                    break;
                case 2:
                    gameState.player3Pos.y += 1;
                    break;
                case 3:
                    gameState.player4Pos.y += 1;
                    break;
            }

            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval)
                minEval = eval;

            switch (turn) {
                case 0:
                    gameState.player1Pos.y -= 1;
                    break;
                case 1:
                    gameState.player2Pos.y -= 1;
                    break;
                case 2:
                    gameState.player3Pos.y -= 1;
                    break;
                case 3:
                    gameState.player4Pos.y -= 1;
                    break;
            }

            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][3]) {
            switch (turn) {
                case 0:
                    gameState.player1Pos.x -= 1;
                    break;
                case 1:
                    gameState.player2Pos.x -= 1;
                    break;
                case 2:
                    gameState.player3Pos.x -= 1;
                    break;
                case 3:
                    gameState.player4Pos.x -= 1;
                    break;
            }
            double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval)
                minEval = eval;

            switch (turn) {
                case 0:
                    gameState.player1Pos.x += 1;
                    break;
                case 1:
                    gameState.player2Pos.x += 1;
                    break;
                case 2:
                    gameState.player3Pos.x += 1;
                    break;
                case 3:
                    gameState.player4Pos.x += 1;
                    break;
            }

            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        switch (turn) {
            case 0:
                if (gameState.player1UsedWallNo >= gameState.player1WallNo) Break = 1;
                break;
            case 1:
                if (gameState.player2UsedWallNo >= gameState.player2WallNo) Break = 1;
                break;
            case 2:
                if (gameState.player3UsedWallNo >= gameState.player3WallNo) Break = 1;
                break;
            case 3:
                if (gameState.player4UsedWallNo >= gameState.player4WallNo) Break = 1;
                break;
        }

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'h';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    switch (turn) {
                        case 0:
                            gameState.player1UsedWallNo++;
                            break;
                        case 1:
                            gameState.player2UsedWallNo++;
                            break;
                        case 2:
                            gameState.player3UsedWallNo++;
                            break;
                        case 3:
                            gameState.player4UsedWallNo++;
                            break;
                    }

                    double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    unBlockCell(newWall);
                    switch (turn) {
                        case 0:
                            gameState.player1UsedWallNo--;
                            break;
                        case 1:
                            gameState.player2UsedWallNo--;
                            break;
                        case 2:
                            gameState.player3UsedWallNo--;
                            break;
                        case 3:
                            gameState.player4UsedWallNo--;
                            break;
                    }

                    if (eval < minEval)
                        minEval = eval;

                    beta = fmin(beta, eval);
                    if (beta <= alpha)
                        Break = 1;
                }
            }

        for (int wallX = 1; !Break && wallX < gameState.size; wallX++)
            for (int wallY = 0; !Break && wallY < gameState.size - 1; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'v';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    switch (turn) {
                        case 0:
                            gameState.player1UsedWallNo++;
                            break;
                        case 1:
                            gameState.player2UsedWallNo++;
                            break;
                        case 2:
                            gameState.player3UsedWallNo++;
                            break;
                        case 3:
                            gameState.player4UsedWallNo++;
                            break;
                    }
                    double eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    unBlockCell(newWall);
                    switch (turn) {
                        case 0:
                            gameState.player1UsedWallNo--;
                            break;
                        case 1:
                            gameState.player2UsedWallNo--;
                            break;
                        case 2:
                            gameState.player3UsedWallNo--;
                            break;
                        case 3:
                            gameState.player4UsedWallNo--;
                            break;
                    }

                    if (eval < minEval)
                        minEval = eval;
                    beta = fmin(beta, eval);
                    if (beta <= alpha)
                        Break = 1;
                }
            }
        return minEval;
    }
}