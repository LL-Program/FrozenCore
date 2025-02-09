#pragma once

#include "../../raylib.h"
#include <vector>

class SpriteSheet
{
public:
    SpriteSheet();
    SpriteSheet(const char *file, int spriteWidth, int spriteHeight, float scale);
    ~SpriteSheet();

    void Load(const char *file, int spriteWidth, int spriteHeight, float scale);
    void Draw(int index, Vector2 position) const;
    void DrawRec(int index, Rectangle sourceRec, Vector2 position) const;
    void Scale(float scaleFactor);
    void Unload();

    Texture2D GetTexture() const;
    Vector2 GetSpriteSize() const;
    Rectangle GetSprite(int indexX, int indexY) const;

    Texture2D texture;
    int spriteWidth;
    int spriteHeight;
    bool isLoaded;
    float scale;
};
