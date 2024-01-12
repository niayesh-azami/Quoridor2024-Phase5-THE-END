int getNewGame() {

    int screenWidth = 600;
    int screenHeight = 300;
    int newGameState = 1;

    InitWindow(screenWidth, screenHeight, "Opponent Type");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                newGameState ^= 1;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return newGameState;

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText("Do You Want To Play A New Game? ", 85, 80, 25, ColorAlpha(WHITE, 1));

        if (newGameState) {
            DrawText("YES", 150, 170, 27, ColorAlpha(BLUE, 0.3));
            DrawText("NO", 400, 170, 27, ColorAlpha(WHITE, 1));
        }

        else {
            DrawText("Yes", 150, 170, 27, ColorAlpha(WHITE, 1));
            DrawText("No", 400, 170, 27, ColorAlpha(BLUE, 0.3));
        }

        EndDrawing();
    }
}