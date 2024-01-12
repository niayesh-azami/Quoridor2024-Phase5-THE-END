int getOpponentType(int player) {

    int screenWidth = 600;
    int screenHeight = 300;
    int whichOpponent = 0;

    InitWindow(screenWidth, screenHeight, "Opponent Type");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                whichOpponent ^= 1;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return whichOpponent;

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText(TextFormat("Choose Player %d's Type : ", player), 155, 80, 25, ColorAlpha(WHITE, 1));

        if (!whichOpponent) {
            DrawText("Play With A Friend", 60, 170, 20, ColorAlpha(BLUE, 0.3));
            DrawText("Play With Mr. Jabal", 340, 170, 20, ColorAlpha(WHITE, 1));
        }

        else {
            DrawText("Play With A Friend", 60, 170, 20, ColorAlpha(WHITE, 1));
            DrawText("Play With Mr. Jabal", 340, 170, 20, ColorAlpha(BLUE, 0.3));
        }

        EndDrawing();
    }

    CloseWindow();
}
