#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"
#include "tilemap.h"

typedef enum Mode
{
    MODE_SELECT,
    MODE_DRAW,
    MODE_ERASE
}
Mode;

// TODO: Implement copy and paste
int main()
{
    const int tileSize = 12;
    const int upscaleFactor = 5;

    const int _tileSizeView = tileSize * upscaleFactor;

    int tileSizeView = _tileSizeView;

    const int windowWidth = 960;
    const int windowHeight = 540;

    InitWindow(windowWidth, windowHeight, "Tilemap Editor");

    InitAudioDevice();

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // int monitor = GetCurrentMonitor();
    // int refreshRate = GetMonitorRefreshRate(monitor);
    // SetTargetFPS(2 * refreshRate);

    const Color gridColor = {172, 172, 172, 255};
    const Color borderColor = {255, 128, 128, 255};
    const Color hoverColor = {128, 255, 255, 32};
    const Color selectionColor = {128, 128, 255, 64};
    const Color selectionBorderColor = {64, 64, 255, 128};

    const Sound placeSound = LoadSound("../resources/place.wav");
    const Sound eraseSound = LoadSound("../resources/erase.wav");
    const Sound saveSound = LoadSound("../resources/save.wav");
    const Sound loadSound = LoadSound("../resources/load.wav");

    int cameraX = 0, cameraY = 0;
    int panStartX = 0, panStartY = 0;
    float zoom = 1.0f;

    bool isPanning = false;
    bool isSelecting = false;
    bool isSelectionActive = false;

    int selectionStartX = 0, selectionStartY = 0;
    int selectionEndX = 0, selectionEndY = 0;

    Texture2D tilesetTexture = LoadTexture("../resources/tileset4x4@12x12.png");

    const unsigned int tileOffsets[] = { 15, 11, 12, 8, 3, 7, 0, 4, 14, 10, 13, 9, 2, 6, 1, 5 };

    Mode activeMode = MODE_SELECT;

    InitializeTilemap();

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        int mouseX = (int)mouse.x;
        int mouseY = (int)mouse.y;

        int hoverX = (mouseX + cameraX) / tileSizeView;
        int hoverY = (mouseY + cameraY) / tileSizeView;

        if(hoverX < 0)
        {
            hoverX = 0;
        }
        else if(hoverX > tilemapWidth - 1)
        {
            hoverX = tilemapWidth - 1;
        }

        if(hoverY < 0)
        {
            hoverY = 0;
        }
        else if(hoverY > tilemapHeight - 1)
        {
            hoverY = tilemapHeight - 1;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
            panStartX = cameraX + mouseX;
            panStartY = cameraY + mouseY;

            isPanning = true;
        }
        
        if(isPanning)
        {
            cameraX = panStartX - mouseX;
            cameraY = panStartY - mouseY;

            if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE))
            {
                isPanning = false;
            }
        }

        float scroll = GetMouseWheelMove();
        if(scroll > 0)
        {
            zoom += 0.1f;
            if(zoom > 2.0f) zoom = 2.0f;
            tileSizeView = (int)(_tileSizeView * zoom);
        }
        else if(scroll < 0)
        {
            zoom -= 0.1f;
            if(zoom < 0.5f) zoom = 0.5f;
            tileSizeView = (int)(_tileSizeView * zoom);
        }

        if(IsKeyPressed(KEY_S))
        {
            if(IsKeyDown(KEY_LEFT_CONTROL))
            {
                SaveTilemap("../resources/tilemap.bin");
                PlaySound(saveSound);
            }
            else
            {
                activeMode = MODE_SELECT;
            }
        }

        if(IsKeyPressed(KEY_O) && IsKeyDown(KEY_LEFT_CONTROL))
        {
            LoadTilemap("../resources/tilemap.bin");
            PlaySound(loadSound);
        }

        if(IsKeyPressed(KEY_B))
        {
            activeMode = MODE_DRAW;
        }

        if(IsKeyPressed(KEY_E))
        {
            activeMode = MODE_ERASE;
        }

        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A))
        {
            selectionStartX = 0;
            selectionStartY = 0;

            selectionEndX = tilemapWidth - 1;
            selectionEndY = tilemapHeight - 1;

            isSelectionActive = true;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isSelecting && activeMode == MODE_SELECT)
        {
            selectionStartX = hoverX;
            selectionStartY = hoverY;

            isSelecting = true;
            isSelectionActive = false;
        }

        if(isSelecting)
        {
            selectionEndX = hoverX;
            selectionEndY = hoverY;
        }

        int selectionMinX = selectionStartX < selectionEndX ? selectionStartX : selectionEndX;
        int selectionMinY = selectionStartY < selectionEndY ? selectionStartY : selectionEndY;

        int selectionMaxX = selectionStartX > selectionEndX ? selectionStartX : selectionEndX;
        int selectionMaxY = selectionStartY > selectionEndY ? selectionStartY : selectionEndY;

        int selectionWidth = selectionMaxX - selectionMinX + 1;
        int selectionHeight = selectionMaxY - selectionMinY + 1;

        if(isSelecting && (selectionWidth > 1 || selectionHeight > 1))
        {
            isSelectionActive = true;
        }

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isSelecting = false;
        }

        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)
        || (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && isSelectionActive && activeMode == MODE_SELECT))
        {
            isSelectionActive = false;
        }

        // Really you only need to update around the border
        if((IsKeyPressed(KEY_X) || IsKeyPressed(KEY_DELETE)) && isSelectionActive)
        {
            for (int y = 0; y < selectionHeight; y++)
            {
                for (int x = 0; x < selectionWidth; x++)
                {
                    RemoveTile(selectionMinX + x, selectionMinY + y);
                }
            }
            PlaySound(eraseSound);
        }

        // Questionable
        if(IsKeyPressed(KEY_F) && isSelectionActive)
        {
            for (int y = 0; y < selectionHeight; y++)
            {
                for (int x = 0; x < selectionWidth; x++)
                {
                    PlaceTile(selectionMinX + x, selectionMinY + y);
                }
            }
            PlaySound(placeSound);
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (!isSelectionActive
        || (hoverX >= selectionMinX && hoverY >= selectionMinY
        && hoverX <= selectionMaxX && hoverY <= selectionMaxY)))
        {
            if(activeMode == MODE_DRAW)
            {
                bool placed = PlaceTile(hoverX, hoverY);
                if(placed) PlaySound(placeSound);
            }
            else if(activeMode == MODE_ERASE)
            {
                bool erased = RemoveTile(hoverX, hoverY);
                if(erased) PlaySound(eraseSound);
            }

        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int gridHeightView = tilemapHeight * tileSizeView;

        for (int x = 0; x <= tilemapWidth; x++)
        {
            const int viewX = x * tileSizeView - cameraX;
            DrawLine(viewX, 0 - cameraY, viewX, gridHeightView - cameraY, gridColor);
        }

        const int gridWidthView = tilemapWidth * tileSizeView;

        for (int y = 0; y <= tilemapHeight; y++)
        {
            const int viewY = y * tileSizeView - cameraY;
            DrawLine(0 - cameraX, viewY, gridWidthView - cameraX, viewY, gridColor);
        }
        
        DrawRectangleLines(0 - cameraX, 0 - cameraY, gridWidthView, gridHeightView, borderColor);

        for (int y = 0; y < tilemapHeight; y++)
        {
            for (int x = 0; x < tilemapWidth; x++)
            {
                if(TileExists(x, y))
                {
                    Tile tile = tilemap[y][x];

                    unsigned int i = tileOffsets[tile >> 1];

                    unsigned int u = i % 4;
                    unsigned int v = i / 4;

                    Rectangle dest = {
                        .x = x * tileSizeView - cameraX,
                        .y = y * tileSizeView - cameraY,
                        .width = tileSizeView,
                        .height = tileSizeView
                    };

                    Rectangle src = {
                        .x = u * tileSize,
                        .y = v * tileSize,
                        .width = tileSize,
                        .height = tileSize
                    };

                    DrawTexturePro(tilesetTexture, src, dest, Vector2Zero(), 0, WHITE);
                }
            }
        }

        if (isSelectionActive)
        {
            int selectionMinXView = selectionMinX * tileSizeView - cameraX;
            int selectionMinYView = selectionMinY * tileSizeView - cameraY;

            int selectionMaxXView = selectionMaxX * tileSizeView - cameraX;
            int selectionMaxYView = selectionMaxY * tileSizeView - cameraY;

            int selectionWidthView = selectionWidth * tileSizeView;
            int selectionHeightView = selectionHeight * tileSizeView;

            DrawRectangle(selectionMinXView, selectionMinYView, selectionWidthView, selectionHeightView, selectionColor);
            DrawRectangleLines(selectionMinXView, selectionMinYView, selectionWidthView, selectionHeightView, selectionBorderColor);
        }

        const int hoverXView = hoverX * tileSizeView - cameraX;
        const int hoverYView = hoverY * tileSizeView - cameraY;

        DrawRectangle(hoverXView, hoverYView, tileSizeView, tileSizeView, selectionColor);
        DrawRectangleLines(hoverXView, hoverYView, tileSizeView, tileSizeView, selectionBorderColor);

        DrawFPS(8, 8);

        char buf[64];

        sprintf(buf, "MODE: %d", activeMode);
        DrawText(buf, 8, 8 + 20 + 8, 20, BLUE);

        if(TileExists(hoverX, hoverY))
        {
            sprintf(buf, "TILE: %d", tilemap[hoverY][hoverX]);
            DrawText(buf, 8, 8 + 20 + 8 + 20 + 8, 20, BLUE);
        }

        if(activeMode == MODE_SELECT && isSelectionActive)
        {
            sprintf(buf, "SELECT: %dx%d", selectionWidth, selectionHeight);
            DrawText(buf, 8, 8 + 20 + 8 + 20 + 8 + 20 + 8, 20, BLUE);
        }

        EndDrawing();
    }

    UnloadTexture(tilesetTexture);

    CloseAudioDevice();

    UnloadSound(placeSound);
    UnloadSound(eraseSound);
    UnloadSound(saveSound);
    UnloadSound(loadSound);

    CloseWindow();

    return 0;
}
