#include "spriteSheet.hpp"

SpriteSheet::SpriteSheet() : texture{0}, spriteWidth{0}, spriteHeight{0}, scale{1.0f} {}

SpriteSheet::~SpriteSheet()
{
    Unload();
}

void SpriteSheet::Load(const char *fileName, int spriteWidth, int spriteHeight, float scale)
{
    texture = LoadTexture(fileName);
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->scale = scale;
}

void SpriteSheet::Unload()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }
}

Rectangle SpriteSheet::GetSprite(int indexX, int indexY) const
{
    return {
        static_cast<float>(indexX * spriteWidth),
        static_cast<float>(indexY * spriteHeight),
        static_cast<float>(spriteWidth),
        static_cast<float>(spriteHeight)};
}

void SpriteSheet::Draw(int index, Vector2 position) const
{
    int cols = texture.width / spriteWidth;
    int row = index / cols;
    int col = index % cols;

    Rectangle sourceRec = {static_cast<float>(col * spriteWidth), static_cast<float>(row * spriteHeight),
                           static_cast<float>(spriteWidth), static_cast<float>(spriteHeight)};
    Vector2 origin = {static_cast<float>(spriteWidth) / 4.0f - 3.1f, static_cast<float>(spriteHeight) / 4.0f - 3.1f};
    Vector2 scaledPosition = {position.x, position.y};

    DrawTexturePro(texture, sourceRec,
                   {scaledPosition.x, scaledPosition.y, spriteWidth * scale, spriteHeight * scale},
                   origin, 0.0f, WHITE);
}

void SpriteSheet::Scale(float scaleFactor)
{
    scale = scaleFactor;
}