#include "Item.hpp"

GameItem::GameItem(const char *name, int id, SpriteSheet* sheet, int shardscost)
{
    this->name = name;
    this->id = id;
    this->sheet = sheet;
    this->shardscost = shardscost;
}

void GameItem::DrawDropped(Vector2 position, Player &player, float deltaTime)
{
    const float floatSpeed = 20.0f;
    const float floatHeight = 5.0;
    if (IsDropped) 
    {
        if (this->droppedFrame >= UP_DOWN_SPEED)
        {
            if (this->goingUp)
            {
                this->droppedPos -= 1.0f;
                if (this->droppedPos <= -floatHeight)
                    this->goingUp = false;
            }
            else
            {
                this->droppedPos += 1.0f;
                if (this->droppedPos >= floatHeight)
                    this->goingUp = true;
            }

            this->droppedFrame = 0;
        }

        this->droppedFrame += 1;

        this->sheet->Draw(0, {position.x, position.y + this->droppedPos});

        float distance = Vector2Distance(position, player.position);

        if (distance < ITEM_DETECTION_RANGE)
        {
            if (IsGamepadAvailable(MAIN_GAMEPAD))
            {
                controllerIconsSheet.Draw(XBOX_X_BUTTON, {position.x + 5, position.y - 30 + this->droppedPos});
            }
            else
            {
                keyboardIconsSheet.Draw(KEYBOARD_ACTION_BUTTON_E, {position.x + 5, position.y - 30 + this->droppedPos});
            }

            if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
            {
                // If its a shard
                if (this->id == 1 || this->id == 2 || this->id == 3) 
                {
                    player.shards += this->shardscost;
                    this->IsDropped = 0;
                }

                else if (AddItemToInventory(*player.inventory, this->id))
                {
                    std::cout << "Added Item : " << this->name << std::endl;
                    this->IsDropped = 0;
                }

            }
        }
    }
}