#include "icicle.hpp"

void UpdateIcicle(Icicle &icicle, std::vector<EnvItem> &envItems, Player &player, float deltaTime)
{
    if (!icicle.isFalling && !icicle.hasFallen)
    {
        if (player.position.x > icicle.position.x - 20 && player.position.x < icicle.position.x + 68)
        {
            icicle.isFalling = true;
            icicle.hasFallen = true;
        }
    }

    if (icicle.isFalling)
    {
        icicle.position.y += icicle.speed * deltaTime;

        for (auto &env : envItems)
        {
            if (env.blocking && CheckCollisionRecs({icicle.position.x, icicle.position.y, 48, 96}, env.rect))
            {
                icicle.isFalling = false;
                icicle.OnGround = true;
                icicle.speed = 0;
                icicle.position.y = env.rect.y - 96;
                break;
            }
        }

        Rectangle icicleRect = {icicle.position.x, icicle.position.y, 48, 96};
        Rectangle playerRect = {player.position.x, player.position.y, 50, 100};

        if (CheckCollisionRecs(icicleRect, playerRect))
        {
            player.life -= 10.0f;        
            icicle.isFalling = false;              
            icicle.position.y += 50; 
        }


        if (icicle.position.y > SCREEN_HEIGHT)
        {
            icicle.position.y = -100; 
            icicle.isFalling = true;
            icicle.speed = ICICLE_FALL_SPD;
        }
    }
}

void DrawIcicle(Icicle &icicle)
{
    if (DEBUG_MODE_ON) DrawRectangle(icicle.position.x, icicle.position.y, 48, 96, BLUE);
    if (!icicle.OnGround) icicleSheet.Draw(0, {icicle.position.x, icicle.position.y});
}