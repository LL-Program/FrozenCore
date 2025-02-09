#include "InventoryGUI.hpp"

void drawInventoryGUI(Player *player){
    // GUIElement hud;
    // hud.LoadTextureFromImageCustom(img);
    // UnloadImage(img);
    // hud.SetPosition({30, 900});
    inventoryGUI.Draw(0, {50, 930});
    if (player->inventory->at(player->selectedItem) != -1)
    {
        GetItemByID(player->inventory->at(player->selectedItem))->sheet->Draw(0, {70, 950});
    }
}   