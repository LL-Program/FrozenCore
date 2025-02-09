#pragma once

#include "../../raylib.h"

class Sprite
{
public:
    Sprite();
    Sprite(const char* &file);
    ~Sprite();

    void Load(const char* &file);
    void Draw(Vector2 position) const;
    void DrawRec(Rectangle sourceRec, Vector2 position) const;
    void Unload();

    Texture2D GetTexture() const;

    Texture2D texture;
    bool isLoaded;
};