#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define tilemapWidth 32
#define tilemapHeight 18

// 5-bits:
// The first bit (0b00001) determines whether the tile is empty or solid.
// The four other bits (0b11110) correspond to the respective connections: top, right, bottom, and left.
typedef uint8_t Tile;

Tile tilemap[tilemapHeight][tilemapWidth];

bool TileExists(int x, int y)
{
    return
    (
        x >= 0 &&
        x < tilemapWidth &&
        y >= 0 &&
        y < tilemapHeight &&
        (tilemap[y][x] & 0b00001) == 1
    );
}

void InitializeTilemap()
{
    for (int y = 0; y < tilemapHeight; y++)
    {
        for (int x = 0; x < tilemapWidth; x++)
        {
            tilemap[y][x] = 0b00000;
        }
    }
}

void CollapseTile(int x, int y)
{
    tilemap[y][x] &= 0b00001;
    if(TileExists(x, y - 1)) tilemap[y][x] |= 0b00011;
    if(TileExists(x + 1, y)) tilemap[y][x] |= 0b00101;
    if(TileExists(x, y + 1)) tilemap[y][x] |= 0b01001;
    if(TileExists(x - 1, y)) tilemap[y][x] |= 0b10001;
}

void CollapseNeighbors(int x, int y)
{
    if(TileExists(x, y - 1)) CollapseTile(x, y - 1); // Top
    if(TileExists(x + 1, y)) CollapseTile(x + 1, y); // Right
    if(TileExists(x, y + 1)) CollapseTile(x, y + 1); // Bottom
    if(TileExists(x - 1, y)) CollapseTile(x - 1, y); // Left
}

bool PlaceTile(int x, int y)
{
    if(TileExists(x, y)) return false;
    tilemap[y][x] |= 0b00001;
    CollapseTile(x, y);
    CollapseNeighbors(x, y);
    return true;
}

bool RemoveTile(int x, int y)
{
    if(!TileExists(x, y)) return false;
    tilemap[y][x] &= 0b11110;
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