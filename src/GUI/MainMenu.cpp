#include "MainMenu.hpp"

void drawMainMenuBG(float delta) 
{
    // UPDATE
    ShopPreviewAnimation.Update(delta);
    PlayerPreviewAnimation.Update(delta);
    TorchPreviewAnimation.Update(delta);
    // T1: 196I, T2: 276I
    //ENV
    tileSheet.Draw(276, {-7 * 48, 2 * 48});
    tileSheet.Draw(196, {-6 * 48, 2 * 48});
    tileSheet.Draw(276, {-5 * 48, 2 * 48});
    tileSheet.Draw(196, {-4 * 48, 2 * 48});
    tileSheet.Draw(276, {-3 * 48, 2 * 48});
    tileSheet.Draw(276, {-2 * 48, 2 * 48});
    tileSheet.Draw(196, {-1 * 48, 2 * 48});
    tileSheet.Draw(276, {0 * 48, 2 * 48});
    tileSheet.Draw(196, {1 * 48, 2 * 48});
    tileSheet.Draw(196, {2 * 48, 2 * 48});
    tileSheet.Draw(196, {3 * 48, 2 * 48});
    tileSheet.Draw(276, {4 * 48, 2 * 48});
    tileSheet.Draw(276, {5 * 48, 2 * 48});
    tileSheet.Draw(196, {6 * 48, 2 * 48});
    tileSheet.Draw(276, {7 * 48, 2 * 48});
    //ENTITIES
    ShopPreviewAnimation.Draw({3 * 48, 0 * 48 + 4});
    PlayerPreviewAnimation.Draw({-4 * 48, 0 * 48 + 4});
    // TORCH LEFT
    TorchPreviewAnimation.Draw({-6 * 48, -2 * 48});
    //TORCH RIGHT
    TorchPreviewAnimation.Draw({5 * 48, -2 * 48});
    //ICE 1
    icicleSheet.Draw(0, {6 * 48, -4 * 48});
    icicleSheet.Draw(7, {5 * 48, -4 * 48});
    icicleSheet.Draw(2, {4 * 48, -4 * 48});
    icicleSheet.Draw(4, {3 * 48, -4 * 48});
    icicleSheet.Draw(3, {2 * 48, -4 * 48});
    icicleSheet.Draw(1, {1 * 48, -4 * 48});
    icicleSheet.Draw(6, {0 * 48, -4 * 48});
    icicleSheet.Draw(2, {-1 * 48, -4 * 48});
    icicleSheet.Draw(4, {-2 * 48, -4 * 48});
    icicleSheet.Draw(2, {-3 * 48, -4 * 48});
    icicleSheet.Draw(7, {-4 * 48, -4 * 48});
    icicleSheet.Draw(5, {-5 * 48, -4 * 48});
    icicleSheet.Draw(6, {-6 * 48, -4 * 48});
    icicleSheet.Draw(3, {-7 * 48, -4 * 48});
}

void drawMainCreditsBG(float delta) 
{
    PlayerPreviewAnimation.Update(delta);
    PlayerPreviewAnimation.Draw({-4 * 48, 0 * 48 + 4});
}

void drawKillScreenBG(float delta) 
{
    ShopPreviewAnimation.Update(delta);
    ShopPreviewAnimation.Draw({-1 * 48 + 20, 0 * 48 + 4});
}