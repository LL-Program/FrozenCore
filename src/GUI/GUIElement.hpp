#pragma once

#include "../../raylib.h"
#include "../Utils/spriteSheet.hpp"

class GUIElement
{
private:
    SpriteSheet* sheet;
    Vector2 position;
    Vector2 size;

public:
    GUIElement();
    GUIElement(SpriteSheet* sheet, Vector2 pos, Vector2 size);

    void Draw() const;
    bool IsClicked(Vector2 mousePos) const;
    void SetPosition(Vector2 newPos);
    Vector2 GetPosition() const;
    void SetSheet(SpriteSheet* sheet);

    int index = 0;
};
