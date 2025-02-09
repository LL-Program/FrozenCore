#include "parallaxBackground.hpp"

ParallaxBackground::ParallaxBackground(Texture2D *textures, float *speeds, int layerCount, int screenWidth)
    : layers(textures), speeds(speeds), layerCount(layerCount), screenWidth(screenWidth)
{
    positions = new Vector2[layerCount];
    for (int i = 0; i < layerCount; i++)
    {
        positions[i] = {0.0f, 0.0f};
    }
}

ParallaxBackground::~ParallaxBackground()
{
    delete[] positions;
}

void ParallaxBackground::Update(float deltaTime)
{
    for (int i = 0; i < layerCount; i++)
    {
        positions[i].x -= speeds[i] * deltaTime;

        if (positions[i].x <= -layers[i].width)
        {
            positions[i].x += layers[i].width;
        }
    }
}

void ParallaxBackground::Draw() const
{
    for (int i = 0; i < layerCount; i++)
    {
        DrawTexture(layers[i], static_cast<int>(positions[i].x), static_cast<int>(positions[i].y), WHITE);
        DrawTexture(layers[i], static_cast<int>(positions[i].x + layers[i].width), static_cast<int>(positions[i].y), WHITE);
    }
}
