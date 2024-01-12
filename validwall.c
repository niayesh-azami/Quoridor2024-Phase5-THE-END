#include "aStar.c"

int wallCanGo(int PlayerSize, int xStart, int yStart, int xEnd) {

    // prevent the wall from going on the edge of the board
    xStart = (xStart - 50) / PlayerSize, yStart = (yStart - 100) / PlayerSize;
    xEnd = (xEnd - 50) / PlayerSize;
    if (xStart != xEnd)
        return (xStart >= 0 && xStart <= gameState.size - 2 && yStart >= 1 && yStart <= gameState.size - 1);
    else
        return (xStart >= 1 && xStart <= gameState.size - 1 && yStart >= 0 && yStart<= gameState.size - 2);
}

int overLapWall(struct wall newWall) {
    int x = newWall.x, y = newWall.y;
    if (newWall.dir == 'v' || newWall.dir == 'V')
        return (wallForEachCell[x][y][3] || wallForEachCell[x][y + 1][3]);
    else
        return (wallForEachCell[x][y][0] || wallForEachCell[x + 1][y][0]);
}

void blockCell(struct wall w) {
    int x = w.x, y = w.y;

    // block edges of the graph :
    if (w.dir == 'v' || w.dir == 'V') {
        wallForEachCell[x][y][3] = 1;
        wallForEachCell[x][y + 1][3] = 1;
        wallForEachCell[x - 1][y][1] = 1;
        wallForEachCell[x - 1][y + 1][1] = 1;
    }
    else {
        wallForEachCell[x][y][0] = 1;
        wallForEachCell[x + 1][y][0] = 1;
        wallForEachCell[x][y - 1][2] = 1;
        wallForEachCell[x + 1][y - 1][2] = 1;
    }
}

void unBlockCell(struct wall w) {
    int x = w.x, y = w.y;

    // unblock edges of the graph :
    if (w.dir == 'v' || w.dir == 'V') {
        wallForEachCell[x][y][3] = 0;
        wallForEachCell[x][y + 1][3] = 0;
        wallForEachCell[x - 1][y][1] = 0;
        wallForEachCell[x - 1][y + 1][1] = 0;
    }
    else {
        wallForEachCell[x][y][0] = 0;
        wallForEachCell[x + 1][y][0] = 0;
        wallForEachCell[x][y - 1][2] = 0;
        wallForEachCell[x + 1][y - 1][2] = 0;
    }
}

int validWall(struct wall newWall) {

    if (overLapWall(newWall)) // check if there is an overlap with another wall :
        return 0;

    blockCell(newWall); // assume it is a valid wall and check if it doesn't block the way for players :

    if (!aStarAlgorithm(gameState.player1Pos, gameState.size - 1)) { // see if there is a way for 1 to win :
        unBlockCell(newWall);
        return 0;
    }
    if (!aStarAlgorithm(gameState.player2Pos, 0)) { // check if there is a way for player 2 to win :
        unBlockCell(newWall);
        return 0;
    }

    return 1;
}