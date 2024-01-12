int closedList[100 + 10][100 + 10];
int front = 0, rear = 0;

struct pPair {
    int f;
    int x, y;
} openList[100 * 100 + 10];

struct cell {
    int f, g, h;
} cellDetails[100 + 10][100 + 10];

void queInsert(int element, int x, int y) {
    int pos = rear;
    while (pos > front && openList[pos - 1].f > element)
        openList[pos] = openList[pos - 1], pos--;
    openList[pos].f = element;
    openList[pos].x = x;
    openList[pos].y = y;
    rear++;
}

struct pPair queFront() {
    front++;
    return openList[front - 1];
}

int queSize() {
    return rear - front;
}


int cnt = 0;

int aStarAlgorithm(struct position startCell, int row) {

    cnt++;
    front = 0, rear = 0;

    memset(closedList, 0, sizeof closedList);

    // set all values to maximum :
    for (int i = 0; i < gameState.size; i++)
        for (int j = 0; j < gameState.size; j++) {
            cellDetails[i][j].f = Mx;
            cellDetails[i][j].g = Mx;
            cellDetails[i][j].h = Mx;
        }

    // update values for the root :
    cellDetails[startCell.x][startCell.y].g = 0;
    cellDetails[startCell.x][startCell.y].h = abs(row - startCell.y);
    cellDetails[startCell.x][startCell.y].f = abs(row - startCell.y);

    // insert the root to openlist
    queInsert(cellDetails[startCell.x][startCell.y].f, startCell.x, startCell.y);

    while (queSize() > 0) {

        struct pPair parent = queFront();

        int x = parent.x, y = parent.y;

        closedList[x][y] = 1;

        // the cell on the top of the root :
        if (!wallForEachCell[x][y][0]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = abs(row - y + 1);
            int fNew = gNew + hNew;

            if (y - 1 == row) {
                cellDetails[x][y - 1].g = gNew;
                /*printf("**************\n");
                printf("%d %d %d %d\n", cnt, startCell.x, startCell.y, row);
                for (int i = 0; i < gameState.size; i++) {
                    for (int j = 0; j < gameState.size; j++)
                        printf("%d ", cellDetails[j][i].g);
                    printf("\n");
                }*/
                return 1;
            }

            if (! closedList[x][y - 1] && cellDetails[x][y - 1].f > fNew) {
                queInsert(fNew, x, y - 1);
                cellDetails[x][y - 1].f = fNew;
                cellDetails[x][y - 1].g = gNew;
                cellDetails[x][y - 1].h = hNew;
            }
        }

        // the cell on the right side of the root :
        if (!wallForEachCell[x][y][1]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = abs(row - y);
            int fNew = gNew + hNew;

            if (! closedList[x + 1][y] && cellDetails[x + 1][y].f > fNew) {
                queInsert(fNew, x + 1, y);
                cellDetails[x + 1][y].f = fNew;
                cellDetails[x + 1][y].g = gNew;
                cellDetails[x + 1][y].h = hNew;
            }
        }

        // the cell on the left side of the root :
        if (!wallForEachCell[x][y][2]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = abs(row - y - 1);
            int fNew = gNew + hNew;

            if (y + 1 == row) {
                cellDetails[x][y + 1].g = gNew;
                /*printf("**************\n");
                printf("%d %d %d %d\n", cnt, startCell.x, startCell.y, row);
                for (int i = 0; i < gameState.size; i++) {
                    for (int j = 0; j < gameState.size; j++)
                        printf("%d ", cellDetails[j][i].g);
                    printf("\n");
                }*/
                return 1;
            }

            if (! closedList[x][y + 1] && cellDetails[x][y + 1].f > fNew) {
                queInsert(fNew, x, y + 1);
                cellDetails[x][y + 1].f = fNew;
                cellDetails[x][y + 1].g = gNew;
                cellDetails[x][y + 1].h = hNew;
            }
        }

        // the cell below the root :
        if (!wallForEachCell[x][y][3]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = abs(row - y);
            int fNew = gNew + hNew;

            if (! closedList[x - 1][y] && cellDetails[x - 1][y].f > fNew) {
                queInsert(fNew, x - 1, y);
                cellDetails[x - 1][y].f = fNew;
                cellDetails[x - 1][y].g = gNew;
                cellDetails[x - 1][y].h = hNew;
            }
        }

    }

    /*printf("**************\n");
    printf("%d %d %d %d\n", cnt, startCell.x, startCell.y, row);
    for (int i = 0; i < gameState.size; i++) {
        for (int j = 0; j < gameState.size; j++)
            printf("%d ", cellDetails[j][i].g);
        printf("\n");
    }*/

    return 0;
}