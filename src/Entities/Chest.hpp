#pragma once

#include "../../raylib.h"
#include "../Utils/spriteSheet.hpp"
#include "../Utils/constants.hpp"
#include "player.hpp"
#include "../Configs/SpriteSheetBank.hpp"
#include "../Utils/animation.hpp"
#include "Item.hpp"
#include "../Configs/GameItemBank.hpp"
#include <iostream>

class GameChest
{
public:
    GameChest(int ItemId, SpriteSheet *sheet);

    void Draw(Vector2 Position, Player &player, float deltatime);

    int Itemid;
    bool canbefoundInchests = 1;
    // STATES
    bool isOpen = 0;
    bool AnimationPlaying = 0;

    SpriteSheet *sheet;
    Animation chestAnimation;

    GameItem* innerItem;
};