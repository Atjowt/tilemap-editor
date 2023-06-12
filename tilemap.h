#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define tilemapWidth 32
#define tilemapHeight 18

// 9-bits:
// The first bit (0b|0000|0000|1) determines whether the tile is empty or solid.
// The next four bits (0b|0000|1111|0) correspond to the respective connections: top, right, bottom, and left.
// The last four bits (0b|1111|0000|0) correspond to the respective corners: top-left, top-right, bottom-left, and bottom-right.
typedef uint16_t Tile;

Tile tilemap[tilemapHeight][tilemapWidth];

bool TileExists(int x, int y)
{
    return
    (
        x >= 0 &&
        x < tilemapWidth &&
        y >= 0 &&
        y < tilemapHeight &&
        (tilemap[y][x] & 0b000000001) == 1
    );
}

void InitTilemap()
{
    for (int y = 0; y < tilemapHeight; y++)
    {
        for (int x = 0; x < tilemapWidth; x++)
        {
            tilemap[y][x] = 0b000000000;
        }
    }
}

void CollapseTile(int x, int y)
{
    tilemap[y][x] &= 0b000000001;

    bool top = TileExists(x, y - 1);
    bool right = TileExists(x + 1, y);
    bool bottom = TileExists(x, y + 1);
    bool left = TileExists(x - 1, y);

    if(top) tilemap[y][x] |= 0b000000010;
    if(right) tilemap[y][x] |= 0b000000100;
    if(bottom) tilemap[y][x] |= 0b000001000;
    if(left) tilemap[y][x] |= 0b000010000;
    
    bool topLeft = TileExists(x - 1, y - 1);
    bool topRight = TileExists(x + 1, y - 1);
    bool bottomLeft = TileExists(x - 1, y + 1);
    bool bottomRight = TileExists(x + 1, y + 1);

    if(top && left && !topLeft) tilemap[y][x] |= 0b000100000;
    if(top && right && !topRight) tilemap[y][x] |= 0b001000000;
    if(bottom && left && !bottomLeft) tilemap[y][x] |= 0b010000000;
    if(bottom && right && !bottomRight) tilemap[y][x] |= 0b100000000;
}

void CollapseNeighbors(int x, int y)
{
    bool top = TileExists(x, y - 1);
    bool right = TileExists(x + 1, y);
    bool bottom = TileExists(x, y + 1);
    bool left = TileExists(x - 1, y);

    if(top) CollapseTile(x, y - 1);
    if(right) CollapseTile(x + 1, y);
    if(bottom) CollapseTile(x, y + 1);
    if(left) CollapseTile(x - 1, y);
    
    bool topLeft = TileExists(x - 1, y - 1);
    bool topRight = TileExists(x + 1, y - 1);
    bool bottomLeft = TileExists(x - 1, y + 1);
    bool bottomRight = TileExists(x + 1, y + 1);

    if(topLeft) CollapseTile(x - 1, y - 1);
    if(topRight) CollapseTile(x + 1, y - 1);
    if(bottomLeft) CollapseTile(x - 1, y + 1);
    if(bottomRight) CollapseTile(x + 1, y + 1);
}

bool PlaceTile(int x, int y)
{
    if(TileExists(x, y)) return false;
    tilemap[y][x] |= 0b000000001;
    CollapseTile(x, y);
    CollapseNeighbors(x, y);
    return true;
}

bool RemoveTile(int x, int y)
{
    if(!TileExists(x, y)) return false;
    tilemap[y][x] &= 0b000011110;
    CollapseNeighbors(x, y);
    return true;
}

void SaveTilemap(const char* path)
{
    FILE* file = fopen(path, "wb");
    fwrite(tilemap, sizeof(Tile), tilemapHeight * tilemapWidth, file);
    fclose(file);
}

void LoadTilemap(const char* path) 
{
    FILE* file = fopen(path, "rb");
    fread(tilemap, sizeof(Tile), tilemapHeight * tilemapWidth, file);
    fclose(file);
}