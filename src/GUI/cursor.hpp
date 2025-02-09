#pragma once

#include "../Utils/spriteSheet.hpp"

class GameCursor
{
    public:
        SpriteSheet sprites;
        int state = 0;
        bool stateON = 1;

        void Init();
        void Draw(Vector2 position);
};