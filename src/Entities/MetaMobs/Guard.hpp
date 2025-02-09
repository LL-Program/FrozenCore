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

class Guard
{
public:
    Guard(SpriteSheet *sheet);

    void Draw(Vector2 Position, Player &player, float deltatime);
    // STATES
    bool AnimationPlaying = 0;
    bool isActive = 1;
    bool needItemID = -1;
    bool givesAdvice = 1;
    bool canInteract = 0;
    int advice = KEYBOARD_SHIFT;

    SpriteSheet *sheet;
    Animation GuardAnimation;
};