#pragma once

#include "spriteSheet.hpp"

class Animation
{
    public:
        Animation() = default;
        Animation(SpriteSheet *sheet, int startFrame, int endFrame, float speed, bool loop = true);
        void Update(float deltaTime);
        void Draw(Vector2 position);
        void Reset();

        SpriteSheet *spriteSheet;
        int startFrame;
        int endFrame;
        int currentFrame;
        float frameTime;
        float elapsedTime;
        bool isLooping;
};
