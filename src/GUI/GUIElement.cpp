#include "GUIElement.hpp"

GUIElement::GUIElement() : position({0, 0}), size({0, 0}) {}

GUIElement::GUIElement(SpriteSheet* sheet, Vector2 pos, Vector2 size)
    : position(pos), size(size), sheet(sheet)
{

}

void GUIElement::Draw() const
{
    sheet->Draw(index, position);
}

bool GUIElement::IsClicked(Vector2 mousePos) const
{
    return (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
            mousePos.y >= position.y && mousePos.y <= position.y + size.y);
}

void GUIElement::SetPosition(Vector2 newPos)
{
    position = newPos;
}

Vector2 GUIElement::GetPosition() const
{
    return position;
}

void GUIElement::SetSheet(SpriteSheet* sheet)
{
    sheet = sheet;
}
