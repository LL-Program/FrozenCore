#include "ShopGuard.hpp"

ShopGuard::ShopGuard(const std::vector<int> &ItemIds, SpriteSheet *sheet)
    : Itemids(ItemIds), sheet(sheet), GuardAnimation(sheet, 0, 10, 5.0f, 1), BoxAnimation(&ShopGUISheet, 0, 4, 7.0f, 0)
{
    item1 = GetItemByID(Itemids[0]);
    item2 = GetItemByID(Itemids[1]);
    item3 = GetItemByID(Itemids[2]);
}

void ShopGuard::Draw(Vector2 position, Player& player, float deltaTime)
{
    // GUARD
    if (!oneActive && !twoActive && !threeActive) this->isAll = 1;
    if (!isAll) 
    {
        // aSystem.PlaySoundEffect("ShopGuardIdle", {position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET}, player.position, 1);
        this->GuardAnimation.Update(deltaTime);
        this->GuardAnimation.Draw({position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET});
    } else // Wächter kriegt Herzinfakt weil alles weg ist
    {
        aSystem.PlaySoundEffect("ShopGuardDown", {position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET}, player.position, 0);
        this->sheet->Draw(3, {position.x * 48, position.y * 48 + SPRITES_16_32_Y_OFFSET});
    }

    // BOXES
    float distance = Vector2Distance({position.x * 48, position.y * 48}, player.position);

    if (distance < SHOP_DETECTION_RANGE)
    {
        this->BoxAnimation.startFrame = 0;
        this->BoxAnimation.endFrame = 4;

        this->BoxAnimation.Update(deltaTime);
        if (this->oneActive) this->BoxAnimation.Draw({position.x * 48 - 55, position.y * 48 - 55}); // LEFT
        if (this->twoActive) this->BoxAnimation.Draw({position.x * 48, position.y * 48 - 55});      // CENTER
        if (this->threeActive) this->BoxAnimation.Draw({position.x * 48 + 55, position.y * 48 - 55}); // RIGHT
        if (this->BoxAnimation.currentFrame == this->BoxAnimation.endFrame)
        {

            // ITEMS
            // LEFT
            if (this->oneActive) item1->sheet->Draw(0, {position.x * 48 - 45, position.y * 48 - 47});
            // CENTER
            if (this->twoActive) item2->sheet->Draw(0, {position.x * 48 + 10, position.y * 48 - 47});
            // RIGHT
            if (this->threeActive) item3->sheet->Draw(0, {position.x * 48 + 65, position.y * 48 - 47});


            // CONTROLLS
            if (IsGamepadAvailable(MAIN_GAMEPAD)) 
            {
                // LEFT
                if (this->oneActive)
                    controllerIconsSheet.Draw(XBOX_ACTION_SELECT_LEFT, {position.x * 48 - 40, position.y * 48 - 80});
                // CENTER
                if (this->twoActive)
                    controllerIconsSheet.Draw(XBOX_ACTION_SELECT_UP, {position.x * 48 + 15, position.y * 48 - 80});
                // RIGHT
                if (this->threeActive)
                    controllerIconsSheet.Draw(XBOX_ACTION_SELECT_RIGHT, {position.x * 48 + 70, position.y * 48 - 80});
            } else 
            {
                // LEFT
                // + 15 in the x-position
                if (this->oneActive)
                    keyboardIconsSheet.Draw(KEYBOARD_ACTION_SELECT_LEFT, {position.x * 48 - 40, position.y * 48 - 80});
                // CENTER
                if (this->twoActive)
                    keyboardIconsSheet.Draw(KEYBOARD_ACTION_SELECT_UP, {position.x * 48 + 15, position.y * 48 - 80});
                // RIGHT
                if (this->threeActive)
                    keyboardIconsSheet.Draw(KEYBOARD_ACTION_SELECT_RIGHT, {position.x * 48 + 70, position.y * 48 - 80});
            }

            // LOGIC
            // LEFT
            if (IsKeyPressed(KEY_LEFT) || IsGamepadButtonDown(MAIN_GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            {
                if (player.shards >= item1->shardscost)
                {
                    if (!AddItemToInventory(*player.inventory, item1->id)){
                        aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
                    }
                    player.shards -= item1->shardscost;
                    this->oneActive = 0;
                }
                else
                    aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
            }

            else if (IsKeyPressed(KEY_UP) || IsGamepadButtonDown(MAIN_GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_UP))
            {
                if (player.shards >= item2->shardscost)
                {
                    if (item2->id == 4)
                    {
                        player.life += 20.0f;
                    }
                    else if (!AddItemToInventory(*player.inventory, item2->id))
                    {
                        aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
                    }

                    player.shards -= item2->shardscost;
                    this->twoActive = 0;
                }
                else
                    aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
            }

            else if (IsKeyPressed(KEY_RIGHT) || IsGamepadButtonDown(MAIN_GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            {
                if (player.shards >= item3->shardscost)
                {
                  if(!AddItemToInventory(*player.inventory, item3->id))
                    {
                        aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
                    }

                    player.shards -= item3->shardscost;
                    this->threeActive = 0;
                }
                else
                    aSystem.PlaySoundEffect("Cancel", {position.x * 48, position.y * 48}, player.position, 0);
            }
        }
    }
    else
    {
        if (this->BoxAnimation.currentFrame == this->BoxAnimation.endFrame)
        {
            this->BoxAnimation.startFrame = 4;
            this->BoxAnimation.endFrame = 0;
        }

        if (this->BoxAnimation.currentFrame > 0)
        {
            this->BoxAnimation.Update(deltaTime);
            if (this->oneActive)
                this->BoxAnimation.Draw({position.x * 48 - 55, position.y * 48 - 55}); // LEFT
            if (this->twoActive)
                this->BoxAnimation.Draw({position.x * 48, position.y * 48 - 55});  // CENTER
            if (this->threeActive)
                this->BoxAnimation.Draw({position.x * 48 + 55, position.y * 48 - 55}); // RIGHT
        }
    }
}