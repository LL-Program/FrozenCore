#include "MovingObject.hpp"

MovingObject::MovingObject(float x, float y, float width, float height, float speed)
    : position{x, y}, size{width, height}, speed{speed}, direction{1.0f}, frozen{false}, frozenTime{0.0f} {}

void MovingObject::Update(float deltaTime)
{
    if (frozen)
    {
        frozenTime -= deltaTime;
        if (frozenTime <= 0)
        {
            frozen = false;
        }
    }
    else
    {
        position.x += speed * direction;
        if (position.x <= 0 || position.x + size.x >= GetScreenWidth())
        {
            direction *= -1;
        }
    }
}

void MovingObject::Draw(bool isSelected)
{
    Color color = frozen ? BLUE : DARKGRAY;
    if (isSelected)
        color = RED;
    DrawRectangleV(position, size, color);
}

void MovingObject::Freeze()
{
    frozen = true;
    frozenTime = 5.0f;
}

Vector2 MovingObject::GetPosition() const { return position; }
Vector2 MovingObject::GetSize() const { return size; }
bool MovingObject::IsFrozen() const { return frozen; }