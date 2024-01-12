struct move computerMove;

double heuristic() {
    aStarAlgorithm(gameState.player2Pos, 0);
    int minDisPlayer2 = inF;
    for (int i = 0; i < gameState.size; i++)
        minDisPlayer2 = fmin(cellDetails[i][0].g, minDisPlayer2);

    aStarAlgorithm(gameState.player1Pos, gameState.size - 1);
    int minDisPlayer1 = inF;
    for (int i = 0; i < gameState.size; i++)
        minDisPlayer1 = fmin(cellDetails[i][gameState.size - 1].g, minDisPlayer1);

    return ((double) minDisPlayer1 - (double) minDisPlayer2);
}

double minimax(int isRoot, int depth, int alpha, int beta, int maximizer) {
    if (whoWins() == 1) return (depth + 1) * -inF;
    else if (whoWins() == 2) return (depth + 1) * inF;
    if (!depth)
        return heuristic();

    if (maximizer) {

        double maxEval = -6 * inF;

        int x = gameState.player2Pos.x;
        int y = gameState.player2Pos.y;

        int Break = 0;

        if (!Break && !wallForEachCell[x][y][0]) {
            gameState.player2Pos.y -= 1;
            double eval = minimax(false, depth - 1, alpha, beta, false);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    computerMove.playerPos = gameState.player2Pos;
                }
            }

            gameState.player2Pos.y += 1;

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][1]) {
            gameState.player2Pos.x += 1;
            double eval = minimax(false, depth - 1, alpha, beta, false);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    computerMove.playerPos = gameState.player2Pos;
                }
            }

            gameState.player2Pos.x -= 1;

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][2]) {
            gameState.player2Pos.y += 1;
            double eval = minimax(false, depth - 1, alpha, beta, false);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    computerMove.playerPos = gameState.player2Pos;
                }
            }

            gameState.player2Pos.y -= 1;

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][3]) {
            gameState.player2Pos.x -= 1;
            double eval = minimax(false, depth - 1, alpha, beta, false);

            if (eval > maxEval) {
                maxEval = eval;
                if (isRoot) {
                    computerMove.type = 'p';
                    computerMove.playerPos = gameState.player2Pos;
                }
            }

            gameState.player2Pos.x += 1;

            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (gameState.player2UsedWallNo >= gameState.player2WallNo) Break = 1;

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'h';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    gameState.player2UsedWallNo++;
                    double eval = minimax(false, depth - 1, alpha, beta, false);

                    unBlockCell(newWall);
                    gameState.player2UsedWallNo--;

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
                    gameState.player2UsedWallNo++;
                    double eval = minimax(false, depth - 1, alpha, beta, false);

                    unBlockCell(newWall);
                    gameState.player2UsedWallNo--;

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

        int x = gameState.player1Pos.x;
        int y = gameState.player1Pos.y;

        int Break = 0;

        if (!Break && !wallForEachCell[x][y][0]) {
            gameState.player1Pos.y -= 1;
            double eval = minimax(false, depth - 1, alpha, beta, true);

            gameState.player1Pos.y += 1;
            minEval = fmin(minEval, eval);
            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][1]) {
            gameState.player1Pos.x += 1;
            double eval = minimax(false, depth - 1, alpha, beta, true);

            gameState.player1Pos.x -= 1;
            minEval = fmin(minEval, eval);
            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][2]) {
            gameState.player1Pos.y += 1;
            double eval = minimax(false, depth - 1, alpha, beta, true);

            gameState.player1Pos.y -= 1;
            minEval = fmin(minEval, eval);
            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (!Break && !wallForEachCell[x][y][3]) {
            gameState.player1Pos.x -= 1;
            double eval = minimax(false, depth - 1, alpha, beta, true);

            gameState.player1Pos.x += 1;
            minEval = fmin(minEval, eval);
            beta = fmin(beta, eval);
            if (beta <= alpha)
                Break = 1;
        }

        if (gameState.player1UsedWallNo >= gameState.player1WallNo) Break = 1;

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {
                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = 'h';
                if (validWall(newWall)) {
                    blockCell(newWall);
                    gameState.player1UsedWallNo++;
                    double eval = minimax(false, depth - 1, alpha, beta, true);

                    unBlockCell(newWall);
                    gameState.player1UsedWallNo--;
                    minEval = fmin(minEval, eval);
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
                    gameState.player1UsedWallNo++;
                    double eval = minimax(false, depth - 1, alpha, beta, true);

                    unBlockCell(newWall);
                    gameState.player1UsedWallNo--;
                    minEval = fmin(minEval, eval);
                    beta = fmin(beta, eval);
                    if (beta <= alpha)
                        Break = 1;
                }
            }
        return minEval;
    }
}