#pragma once

#include "../../raylib.h"
#include "../Utils/spriteSheet.hpp"
#include "../Utils/constants.hpp"
#include "player.hpp"
#include "../Configs/SpriteSheetBank.hpp"
#include "Inventory.hpp"
#include <iostream>
class GameItem
{
    public:

        GameItem(const char* name, int id, SpriteSheet* sheet, int shardscost);

        void DrawDropped(Vector2 position, Player &player, float deltaTime);

        int id;
        const char* name;
        int shardscost;
        bool canbefoundInchests = 1;
        // DROPPED
        bool IsDropped = 1;
        float droppedPos = 0.0f;
        int droppedFrame = 0;
        bool goingUp = 0;
        // IF SHARDS
        int count = 0;

        SpriteSheet* sheet;

};