#include "Inventory.hpp"

bool AddItemToInventory(std::vector<int> &inventory, int itemId)
{
    for (int &slot : inventory)
    {
        if (slot == -1)
        {
            slot = itemId;
            return true;
        }
    }
    return false; // (inventory full)
}

void HandleInventoryScrolling(Player* player)
{
    if (GetMouseWheelMove() > 0)
    {
        player->selectedItem = (player->selectedItem - 1 + MAX_ITEMS) % MAX_ITEMS; // Scroll left
    }
    if (GetMouseWheelMove() < 0)
    {
        player->selectedItem = (player->selectedItem + 1) % MAX_ITEMS; // Scroll right
    }

    if (IsGamepadAvailable(MAIN_GAMEPAD))
    { 
        if (IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
        {
            player->selectedItem = (player->selectedItem - 1 + MAX_ITEMS) % MAX_ITEMS;
        }
        if (IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
        {
            player->selectedItem = (player->selectedItem + 1) % MAX_ITEMS;
        }
    }
}