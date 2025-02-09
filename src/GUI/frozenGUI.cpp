#include "frozenGUI.hpp"

void drawFrozenGui(Player *player) 
{

    if (player->temperature >= 50) 
    {
        frozenGUI.Draw(0, {150, 990});
    }
    else if (player->temperature < 50 && player->temperature >= 40) 
    {
        frozenGUI.Draw(1, {150, 990});
    }
    else if (player->temperature < 40 && player->temperature >= 30)
    {
        frozenGUI.Draw(2, {150, 990});
    }
    else if (player->temperature < 30 && player->temperature >= 20)
    {
        frozenGUI.Draw(3, {150, 990});
    }
    else 
    {
        frozenGUI.Draw(4, {150, 990});
    }
}