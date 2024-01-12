int getPlayerCount() {

    int screenWidth = 600;
    int screenHeight = 300;
    int playerCount = 2;

    InitWindow(screenWidth, screenHeight, "Opponent Type");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                playerCount = 6 - playerCount;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return playerCount;

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText("Choose Your Type Of Game: ", 125, 80, 25, ColorAlpha(WHITE, 1));

        if (playerCount == 2) {
            DrawText("2 Player", 120, 170, 25, ColorAlpha(BLUE, 0.3));
            DrawText("4 Player", 370, 170, 25, ColorAlpha(WHITE, 1));
        }

        else {
            DrawText("2 Player", 120, 170, 25, ColorAlpha(WHITE, 1));
            DrawText("4 Player", 370, 170, 25, ColorAlpha(BLUE, 0.3));
        }

        EndDrawing();
    }
    CloseWindow();
}