#include "cursor.hpp"
#include "../Utils/constants.hpp"

void GameCursor::Init()
{
    sprites.Load("resources/GUI/cursor.png", 8, 8, SCALE_FACTOR_8_8);
}

void GameCursor::Draw(Vector2 position)
{
    if (stateON) 
    {
        sprites.Draw(state, position);
    }
}