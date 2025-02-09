#include "Level.hpp"

void DrawEnvItem(EnvItem* item, SpriteSheet* sheet)
{

    sheet->Draw(item->spriteIndex, {item->rect.x, item->rect.y});
}