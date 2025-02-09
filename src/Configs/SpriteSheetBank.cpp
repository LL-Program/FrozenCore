#include "SpriteSheetBank.hpp"

// Define the sprite sheets
SpriteSheet tileSheet;
SpriteSheet playerSheet;
SpriteSheet thermalBombSheet;
SpriteSheet keyboardIconsSheet;
SpriteSheet controllerIconsSheet;
SpriteSheet chestSheet;
SpriteSheet ShopGuardSheet;
SpriteSheet ShopGUISheet;
SpriteSheet frozenGUI;
SpriteSheet inventoryGUI;
SpriteSheet lifeGUI;
SpriteSheet icicleSheet;
SpriteSheet torchSheet1;
SpriteSheet PlayButtonSheet;
SpriteSheet shardsSheet;
SpriteSheet chatBubbleSheet;
SpriteSheet playerDash;
SpriteSheet ItemHeart;
SpriteSheet ItemMechanical;
SpriteSheet Logo;
SpriteSheet arrowGUI;

void InitializeSpriteSheets()
{
    // ID : 0
    tileSheet.Load("resources/Env/tilemap2.png", 16, 16, SCALE_FACTOR_16_16);
    // ID : 1
    playerSheet.Load("resources/player/pl.png", 16, 32, SCALE_FACTOR_16_16);
    // ID : 2
    thermalBombSheet.Load("resources/Entities/Items/thermal_bomb.png", 16, 16, SCALE_FACTOR_ITEM_16_16);
    // ID : 3
    keyboardIconsSheet.Load("resources/GUI/keyboardIcons.png", 16, 16, CONTROLLER_ICONS_SCALE_16_16);
    // ID : 4
    controllerIconsSheet.Load("resources/GUI/controllerIcons.png", 16, 16, CONTROLLER_ICONS_SCALE_16_16);
    // ID : 5
    chestSheet.Load("resources/Env/chest.png", 16, 16, SCALE_FACTOR_16_16);
    // ID: 6
    ShopGuardSheet.Load("resources/Entities/ShopGuard.png", 16, 32, SCALE_FACTOR_16_16);
    // ID: 7
    ShopGUISheet.Load("resources/GUI/shopboxes.png", 16, 16, SCALE_FACTOR_16_16);
    // ID : 8
    frozenGUI.Load("resources/GUI/frozenview.png", 64, 16, SCALE_FACTOR_16_16);
    // ID : 9
    inventoryGUI.Load("resources/GUI/InventoryGUI.png", 128, 128, 1.0f);
    // ID : 10
    lifeGUI.Load("resources/GUI/lifeview.png", 64, 16, SCALE_FACTOR_16_16);
    // ID : 11
    icicleSheet.Load("resources/Env/icicle.png", 16, 32, SCALE_FACTOR_16_16);
    // ID : 12
    torchSheet1.Load("resources/Env/torch.png", 16, 16, SCALE_FACTOR_16_16);
    // ID : 13
    PlayButtonSheet.Load("resources/GUI/PlayButton.png", 16, 16, SCALE_FACTOR_16_16_GUI_MENU);
    // ID : 14
    shardsSheet.Load("resources/Entities/Items/antshards.png", 16, 16, SCALE_FACTOR_ITEM_16_16);
    // ID: 15
    chatBubbleSheet.Load("resources/GUI/chatbubble.png", 16, 16, SCALE_FACTOR_16_16);
    // ID : 16
    playerDash.Load("resources/player/dash.png", 32, 32, SCALE_FACTOR_16_16);
    // ID: 16
    ItemHeart.Load("resources/Entities/Items/heart.png", 16, 16, SCALE_FACTOR_ITEM_16_16);
    // ID: 16
    ItemMechanical.Load("resources/Entities/Items/tr.png", 16, 16, SCALE_FACTOR_ITEM_16_16);
    // ID : 17
    Logo.Load("resources/GUI/Logo.png", 1560, 480, 1.0f);
    // ID: 18
    arrowGUI.Load("resources/GUI/Arrow.png", 16, 16, SCALE_FACTOR_ITEM_16_16);
}
