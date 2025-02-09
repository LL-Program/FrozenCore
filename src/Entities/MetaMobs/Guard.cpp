#include "Guard.hpp"

Guard::Guard(SpriteSheet *sheet)
    : sheet(sheet), GuardAnimation(sheet, 0, 10, 5.0f, 1)
{

}

void Guard::Draw(Vector2 position, Player &player, float deltaTime)
{
    if (!(isActive)) 
    {
        sheet->Draw(3, {position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET});
    } else 
    {
        GuardAnimation.Update(deltaTime);
        GuardAnimation.Draw({position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET});

        if (givesAdvice) 
        {
            float distance = Vector2Distance({position.x * 48, position.y * 48}, player.position);

            if (distance < GUARD_DETECTION_RANGE) 
            {

                if (advice == KEYBOARD_SHIFT)
                {
                    chatBubbleSheet.Draw(0, {position.x * 48, position.y * 48 - 55});
                    if (IsGamepadAvailable(MAIN_GAMEPAD))
                        controllerIconsSheet.Draw(XBOX_ACTION_TRIGGER_RIGHT_DASH, {position.x * 48 + 14, position.y * 48 - 43});
                    else
                        keyboardIconsSheet.Draw(KEYBOARD_SHIFT, {position.x * 48 + 14, position.y * 48 - 44});
                }

                if (advice == KEYBOARD_ACTION_BUTTON_E) 
                {
                    chatBubbleSheet.Draw(0, {position.x * 48, position.y * 48 - 55});
                    if (IsGamepadAvailable(MAIN_GAMEPAD))
                        controllerIconsSheet.Draw(XBOX_X_BUTTON, {position.x * 48 + 14, position.y * 48 - 43});
                    else
                        keyboardIconsSheet.Draw(KEYBOARD_ACTION_BUTTON_E, {position.x * 48 + 14, position.y * 48 - 44});

                    if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) 
                    {
                        if (player.missionentried) player.isFinished = 1;
                        else
                            aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
                    }
                }
            }
        }
    }

    float distance = Vector2Distance({position.x * 48, position.y * 48}, player.position);

    if (distance < GUARD_DETECTION_RANGE)
    {
        if (needItemID != -1 && !isActive) 
        {
            chatBubbleSheet.Draw(0, {position.x * 48, position.y * 48 - 55});
            GetItemByID(needItemID)->sheet->Draw(0, {position.x * 48 + 10, position.y * 48 - 49});

            if (player.inventory->at(player.selectedItem) != -1 && player.inventory->at(player.selectedItem) == needItemID)
            {
                if (IsGamepadAvailable(MAIN_GAMEPAD))
                {
                    controllerIconsSheet.Draw(XBOX_X_BUTTON, {position.x * 48 + 15, position.y * 48 - 80});
                }
                else
                {
                    keyboardIconsSheet.Draw(KEYBOARD_ACTION_BUTTON_E, {position.x * 48 + 15, position.y * 48 - 80});
                }

                if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) 
                {
                    needItemID = -1;
                    isActive = 1;
                    player.missionentried = 1;
                    player.inventory->at(player.selectedItem) = -1;
                }
            }
        }
    }
}