#pragma once

#include "../../raylib.h"

class ParallaxBackground
{
private:
    Texture2D *layers;
    float *speeds;
    int layerCount;
    Vector2 *positions;
    int screenWidth;

public:
    ParallaxBackground(Texture2D *textures, float *speeds, int layerCount, int screenWidth);
    ~ParallaxBackground();
    void Update(float deltaTime);
    void Draw() const;
};
