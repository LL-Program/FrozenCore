#pragma once

#include "../../raylib.h"
#include "../Utils/spriteSheet.hpp"
#include "../Utils/constants.hpp"
#include "player.hpp"
#include "../Configs/SpriteSheetBank.hpp"
#include "../Utils/animation.hpp"
#include "envItem.hpp"
#include <vector>

struct Icicle
{
    Vector2 position;
    float speed;
    bool isFalling;
    bool hasFallen;
    bool OnGround = 0;
};

void UpdateIcicle(Icicle &icicle, std::vector<EnvItem> &envItems, Player &player, float deltaTime);
void DrawIcicle(Icicle &icicle);
void DrawPlayer(Player &player);