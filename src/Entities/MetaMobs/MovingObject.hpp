#pragma once

#include "../../../raylib.h"
#include "../../Configs/SpriteSheetBank.hpp"

class MovingObject
{
private:
    Vector2 position;
    Vector2 size;
    float speed;
    float direction;
    bool frozen;
    float frozenTime;

public:
    MovingObject(float x, float y, float width, float height, float speed);

    void Update(float deltaTime);
    void Draw(bool isSelected);

    Vector2 GetPosition() const;
    Vector2 GetSize() const;

    void Freeze();
    bool IsFrozen() const;
};
