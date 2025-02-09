#include "HeatSource.hpp"

HeatSource::HeatSource(float range, float factor, Vector2 position)
        : range(range), factor(factor), position(position)
{

}

void HeatSource::Update(Player* player)
{
    float distance = Vector2Distance({position.x * 48, position.y * 48}, player->position);
    if (distance < ITEM_DETECTION_RANGE)
    {
        // 1 / 60 Smallest Factor
        // z.B factor  = 1 -> 1 / 60 -> 1+ per Second
        // Can be negative to get colder
        player->temperature += factor / 60;
        player->playerIsHeated = 1;
        player->lastPosition = {HeatSource::position.x * 48, HeatSource::position.y * 48};
    }
}