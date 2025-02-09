#include "Chest.hpp"

GameChest::GameChest(int Itemid, SpriteSheet *sheet)
    : Itemid(Itemid), sheet(sheet), innerItem(GetItemByID(Itemid)), chestAnimation(sheet, 0, 7, 7.0f, 0)
{

}

void GameChest::Draw(Vector2 position, Player &player, float deltaTime)
{

    if (!this->isOpen)
    {
        this->sheet->Draw(0, {position.x * 48, position.y * 48});

        float distance = Vector2Distance({position.x * 48, position.y * 48}, player.position);
        if (distance < ITEM_DETECTION_RANGE)
        {
            if (IsGamepadAvailable(MAIN_GAMEPAD))
            {
                controllerIconsSheet.Draw(XBOX_X_BUTTON, {position.x * 48 + 13, position.y * 48 - 20});
            }
            else
            {
                keyboardIconsSheet.Draw(KEYBOARD_ACTION_BUTTON_E, {(position.x * 48) + 13, (position.y * 48) - 20});
            }

            if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
            {
                this->isOpen = 1;
            }
        }
    } else 
    { 

        // FIXE DIESEN BESCHISSENEN BUG AM 4.2
        this->chestAnimation.Update(deltaTime);
        this->chestAnimation.Draw({position.x * 48, position.y * 48});

        if (this->chestAnimation.endFrame == this->chestAnimation.currentFrame)
        {
            this->innerItem->DrawDropped({position.x * 48 + 10, position.y * 48 - 14}, player, deltaTime);
        }
    }
}