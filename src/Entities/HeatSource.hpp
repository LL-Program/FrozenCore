#pragma once

#include "../../raylib.h"
#include "../Utils/spriteSheet.hpp"
#include "../Utils/constants.hpp"
#include "player.hpp"
#include "../Configs/SpriteSheetBank.hpp"
#include "../Utils/animation.hpp"

class HeatSource
{
public:
    HeatSource(float range, float factor, Vector2 position);

    void Update(Player* player);

    // FACTORS
    float range;
    float factor;
    Vector2 position;

};
