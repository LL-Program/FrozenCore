#pragma once

#include "../../../raylib.h"

#pragma once

#include "../../Utils/spriteSheet.hpp"
#include "../../Utils/constants.hpp"
#include "../../Utils/animation.hpp"
#include "../player.hpp"
#include "../../Configs/SpriteSheetBank.hpp"
#include "../../Configs/GameItemBank.hpp"
#include "../../Configs/SoundBank.hpp"
#include "../Item.hpp"
#include <vector>

class ShopGuard
{
public:
    ShopGuard(const std::vector<int> &ItemIds, SpriteSheet *sheet);

    void Draw(Vector2 Position, Player &player, float deltatime);

    const std::vector<int> &Itemids;
    // STATES
    bool isOpen = 0;
    bool AnimationPlaying = 0;
    bool isAll = 0; // Keine Ahnung was alles ausverkauft auf Englisch heißt
    int articlesbought = 0;
    bool oneActive = 1;
    bool twoActive = 1;
    bool threeActive = 1;

    SpriteSheet* sheet;
    Animation GuardAnimation;
    Animation BoxAnimation;

    GameItem* item1;
    GameItem* item2;
    GameItem* item3;
};