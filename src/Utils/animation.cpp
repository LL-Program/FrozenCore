#include "animation.hpp"

Animation::Animation(SpriteSheet *sheet, int startFrame, int endFrame, float speed, bool loop)
    : spriteSheet(sheet), startFrame(startFrame), endFrame(endFrame), currentFrame(startFrame),
      frameTime(1.0f / speed), elapsedTime(0.0f), isLooping(loop) {}

void Animation::Update(float deltaTime)
{
    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime)
    {
        elapsedTime -= frameTime;
        currentFrame++;

        if (currentFrame > endFrame)
        {
            if (isLooping)
            {
                currentFrame = startFrame;
            }
            else
            {
                currentFrame = endFrame;
            }
        }
    }
}

void Animation::Draw(Vector2 position)
{
    spriteSheet->Draw(currentFrame, position);
}

void Animation::Reset()
{
    currentFrame = startFrame;
    elapsedTime = 0.0f;
}
