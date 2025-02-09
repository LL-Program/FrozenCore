#include "sprite.hpp"
#include <stdexcept>
#include <iostream>

Sprite::Sprite() : texture({0}), isLoaded(false) {}

Sprite::Sprite(const char* &file) : texture({0}), isLoaded(false)
{
    Load(file);
}

Sprite::~Sprite()
{
    if (isLoaded)
    {
        Unload();
    }
}

void Sprite::Load(const char* &file)
{
    if (isLoaded)
    {
        Unload();
    }

    texture = LoadTexture(file);
    if (texture.id == 0)
    {
        return;
    }

    isLoaded = true;
}

void Sprite::Draw(Vector2 position) const
{
    if (isLoaded)
    {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}

void Sprite::DrawRec(Rectangle sourceRec, Vector2 position) const
{
    if (isLoaded)
    {
        DrawTextureRec(texture, sourceRec, position, WHITE);
    }
}

void Sprite::Unload()
{
    if (isLoaded)
    {
        UnloadTexture(texture);
        isLoaded = false;
    }
}

Texture2D Sprite::GetTexture() const
{
    return texture;
}
