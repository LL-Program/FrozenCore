#include "lifeGUI.hpp"

void drawLifeGui(Player *player)
{
   
        if (player->life >= 100)
        {
            lifeGUI.Draw(0, {170, 955});
        }
        else if (player->life >= 80)
        {
            lifeGUI.Draw(1, {170, 955});
        }
        else if (player->life >= 60)
        {
            lifeGUI.Draw(2, {170, 955});
        }
        else if (player->life >= 40)
        {
            lifeGUI.Draw(3, {170, 955});
        }
        else 
        {
            lifeGUI.Draw(4, {170, 955});
        }

}