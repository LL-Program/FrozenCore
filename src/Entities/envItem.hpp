#pragma once

#include "../../raylib.h"
#include "../../raymath.h"
#include "../Utils/spriteSheet.hpp"

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    int spriteSheet;
    int spriteIndex;

} EnvItem;