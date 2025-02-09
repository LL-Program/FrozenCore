#include "../raylib.h"
#include "../raymath.h"
#include "AudioSystem/AudioSystem.hpp"
#include "Utils/spriteSheet.hpp"
#include "Utils/constants.hpp"
#include "Utils/animation.hpp"
#include "Utils/LevelSystem.hpp"
#include "Utils/Font.hpp"
#include "Utils/parallaxBackground.hpp"
#include "Configs/SpriteSheetBank.hpp"
#include "Configs/SoundBank.hpp"
#include "Effects/particles.hpp"
#include "Entities/Chest.hpp"
#include "Entities/Inventory.hpp"
#include "Entities/MetaMobs/ShopGuard.hpp"
#include "Entities/HeatSource.hpp"
#include "Entities/Level.hpp"
#include "Entities/icicle.hpp"
#include "Entities/MetaMobs/Guard.hpp"
#include "Entities/player.hpp"
#include "Entities/Item.hpp"
#include "GUI/frozenGUI.hpp"
#include "GUI/InventoryGUI.hpp"
#include "GUI/cursor.hpp"
#include "GUI/GUIElement.hpp"
#include "GUI/lifeGUI.hpp"
#include "GUI/MainMenu.hpp"
#include "GUI/CustomFont.hpp"

int main(void)
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const char* gameVersion = "1.1.0 PATCHED";
    const char* gameTitle = "FrozenCore 1.1.0";

    InitWindow(screenWidth, screenHeight, gameTitle);
    // MAIN CONSTANTS
    bool MainGameActive = 0;
    bool CreditsScreenActive = 0;
    bool MainMenuActive = 1;
    bool KillScreenActive = 0;
    // CREDITS
    int creditscouter = 0;
    //INIT
    ToggleFullscreen();
    HideCursor();
    SetTargetFPS(60);
    InitializeSpriteSheets();
    InitSounds();
    InitMusic();
    InitFonts();

    // ANIMATIONS
    Animation runAnimation(&tileSheet, 0, 6, 3.0f, true); // Frames 0 to 5, 10 FPS, looping
    Animation playerTurnAnimation(&playerSheet, 54, 58, 4.0f, 1); // FIRST Animation
    Animation torchAnimation1(&torchSheet1, 0, 15, 5.0f, 1);
    GameItem t1 = GameItem("Antique Shards", 1, &shardsSheet, 10);
    GameItem t2 = GameItem("Antique Shards", 2, &shardsSheet, 20);

    GameChest chest = GameChest(0, &chestSheet);
    // PARTICLE
    Particle Particles[PARTICLES_MAX];

    int snowstormParticleCount = 0;

    aSystem.SetMusicVolumeCustom(0.3f); // !!!!!!!
    aSystem.PlayMusic(1);

    // TORCHES
    std::vector<HeatSource> torches = {
        {175.0f, 5.0f, {8, 12}},
        {175.0f, 5.0f, {54, 12}},
        {175.0f, 5.0f, {82, 2}},
        {175.0f, 5.0f, {99, 7}},
        {175.0f, 5.0f, {127, 9}},
        {175.0f, 5.0f, {149, 13}}};

    // ICICLES
    std::vector<Icicle> icicles = {
        {{41 * 48, 6 * 48}, ICICLE_FALL_SPD, false, false},
        {{67 * 48, 6 * 48}, ICICLE_FALL_SPD, false, false},
        {{150 * 48, 6 * 48}, ICICLE_FALL_SPD, false, false}};
    // DROPPED ITEMS
    std::vector<GameItem> droppedItems = {{"Antique Shards", 1, &shardsSheet, 10},
                                          {"Antique Shards", 1, &shardsSheet, 20},
                                          {"Antique Shards", 1, &shardsSheet, 10}

    };

    std::vector<Vector2> droppedItemsPositions = {
        {570, 624},
        {49, 1},
        {68, 3}
    };
    // FONT TEST
    //  FontManager fontManager("resources/QuinqueFive.ttf", 32, 4.0f);
    //  fontManager.StartTyping("Morli ist ein SUPA PIXLER");
    //  SHOP GUARD
    ShopGuard shopGuard1 = ShopGuard({0, 4, 0}, &ShopGuardSheet);
    shopGuard1.oneActive = 0;
    shopGuard1.threeActive = 0;
    Guard guard1 = Guard(&ShopGuardSheet);
    Guard aGuard1 = Guard(&ShopGuardSheet);
    aGuard1.isActive = 0;
    aGuard1.givesAdvice = 0;
    aGuard1.needItemID = 0;
    Guard aGuard2 = Guard(&ShopGuardSheet);
    aGuard2.isActive = 1;
    aGuard2.advice = KEYBOARD_ACTION_BUTTON_E;
    aGuard2.givesAdvice = 1;
    aGuard2.needItemID = -1;

    // PLAYER AND CAMERA
    Player player = Player();
    player.position = Vector2{8 * 48, 8 * 48};
    player.speed = 0;
    player.canJump = false; 
    player.sheet = &playerSheet;
    player.currentAnimation = playerTurnAnimation;


    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = Vector2{screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 5.0f;

    // GAME CHECKS
    bool firstZoom = 0;
    bool playerControllable = 0;
    int framecounter = 0;

    // ---------- MAIN MENU -----------------
    Camera2D MenuCamera = {0};
    MenuCamera.target = {0, 0};
    MenuCamera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    MenuCamera.zoom = 3.0f;
    MenuCamera.rotation = 0.0f;

    // GUI
    GameCursor MenuCursor;
    MenuCursor.Init();
    GUIElement playButton(&PlayButtonSheet, {SCREEN_WIDTH / 2.0f - 48, SCREEN_HEIGHT / 2.0f + 108.0f}, {48, 48});
    GUIElement retryButton(&PlayButtonSheet, {SCREEN_WIDTH / 2.0f - 48, SCREEN_HEIGHT / 2.0f - 200.0f}, {48, 48});

    // ENV
    std::vector<EnvItem>
            envItems = loadLevelData("resources/Level/level.fcl");
    int envItemsLength = envItems.size();


    int cameraOption = 2;

    const char* cameraDescriptions[] = {
        "Follow player center",
        "Follow player center, but clamp to map edges",
        "Follow player center; smoothed",
        "Follow player center horizontally; update player center vertically after landing",
        "Player push camera on getting too close to screen edge"};

    while (!WindowShouldClose())
    {

        float deltaTime = GetFrameTime();
        
        // MAIN GAME
        if (MainGameActive) 
        {

        aSystem.UpdateMusic();
        // PLAYER DEAD
        HandleInventoryScrolling(&player);
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        if (player.life <= 20)
        {
            MainGameActive = 0;
            KillScreenActive = 1;
            aSystem.PlayMusic(3);
        }

        if (player.isFinished) 
        {
            MainGameActive = 0;
            CreditsScreenActive = 1;
            aSystem.PlayMusic(2);
        }

        if (!firstZoom) 
        {
            if (!(framecounter >= 120)) 
            {
                framecounter += 1;
            } else 
            {
                if (camera.zoom > 1.5)
                {
                    camera.zoom -= 2.0 / 60.0;
                    if (camera.zoom < 1.5)
                    {
                        camera.zoom = 1.5;
                    }
                }
                else
                {
                    firstZoom = 1;
                    player.isControllable = 1;
                }
            }
        }
        //torch1.Update({8, 12}, &player);
        for (auto &torch : torches) 
        {
            torch.Update(&player);
        }

        for (auto &icicle : icicles) 
        {
            UpdateIcicle(icicle, envItems, player, deltaTime);
        }

        if(player.position.x >= 113 * 48)
        {
            player.isSnowStorm = 1;
        }
        else 
        {
            player.isSnowStorm = 0;
            ResetSnowstorm(Particles, &snowstormParticleCount);

        }

        // ANIMATIONS UPDATE 
        torchAnimation1.Update(deltaTime);

        if (player.isSnowStorm)
        {
            for (int i = 0; i < 3; i++)
                SpawnSnowStormParticles(Particles, &snowstormParticleCount, player.SnowStormSpawnLeft);

            UpdateSnowStormParticles(Particles, &snowstormParticleCount, deltaTime);
        }
        //idleAnimation.Update(deltaTime);
        // shopboxAnimation.Update(deltaTime);
        // fontManager.Update(deltaTime);


        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f)
            camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R) && DEBUG_MODE_ON)
        {
            camera.zoom = 1.5f;
            player.position = Vector2{400, 280};
            ResetSnowstorm(Particles, &snowstormParticleCount);
        }


        UpdateCameraCenterSmoothFollow(&camera, &player, envItemsLength, deltaTime, screenWidth, screenHeight);
        // UpdateSnowParticles( Particles, &particleCount, deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode2D(camera);


        //------------Environment-------------------
        for (int i = 0; i < envItemsLength; i++) 
        {
            if (DEBUG_MODE_ON)
            {
                if (envItems[i].blocking)
                {
                    DrawRectangleLines(envItems[i].rect.x, envItems[i].rect.y, envItems[i].rect.width, envItems[i].rect.height, RED);
                }
            }
            DrawEnvItem(&envItems[i], &tileSheet);
        }

        int d1 = 0;
        for (auto &item : droppedItems) 
        {
            item.DrawDropped(droppedItemsPositions.at(d1), player, deltaTime);
            d1 += 1;
        }
        chest.Draw({55, 3}, player, deltaTime);
        guard1.Draw({32, 12}, player, deltaTime);
        aGuard1.Draw({62, 12}, player, deltaTime);
        aGuard2.Draw({162, 16}, player, deltaTime);
        shopGuard1.Draw({81, 2}, player, deltaTime);
        t1.DrawDropped({49 * 48, 1 * 48}, player, deltaTime);
        t2.DrawDropped({68 * 48, 3 * 48}, player, deltaTime);

        for (auto &torch : torches)
        {
            torchAnimation1.Draw(torch.position);
        }

        for (auto &icicle : icicles)
        {
            DrawIcicle(icicle);
        }

        for (auto &torch : torches)
        {
           torchAnimation1.Draw({torch.position.x * 48, torch.position.y * 48});
        }
        //------------------------------------------
        // FREEZE TIPP
        if (player.lastPosition == Vector2{8 * 48, 12 * 48})
        {
            ArrowGUIAnimaion.Update(deltaTime);
            ArrowGUIAnimaion.Draw({8 * 48 + 13, 11 * 48});
            DrawCustomFont("Warm yourself up", {8 * 48 - 40, 13 * 48 + 10}, 8, WHITE);
        }
        // DrawSnowParticles(Particles, particleCount);
        DrawPlayer(&player, deltaTime);
        Rectangle playerRect = {player.position.x - 24, player.position.y - 96, 48.0f, 96.0f};
        // -------------------- DEBUG GAME ------------------------------------------------------
        if (DEBUG_MODE_ON)
        {
            DrawRectangleLines(playerRect.x, playerRect.y, playerRect.width, playerRect.height, RED);
            DrawText(TextFormat("SOUND TEST", gameVersion), 800, 300, 15, BLUE);
        }
        //---------------------------------------------------------------------------------------
            EndMode2D();
        // SNOW STORM
        if (player.isSnowStorm) DrawSnowStormParticles(Particles, snowstormParticleCount);
        // DEBUG TEXT
        if (DEBUG_MODE_ON) 
        {
            DrawText(TextFormat("Version %s", gameVersion), 20, 20, 12, LIGHTGRAY);
            DrawText(TextFormat("FPS: %d", GetFPS()), 20, 30, 12, LIGHTGRAY);
            DrawText(TextFormat("Player Position: (%2.0f, %2.0f)", player.position.x, player.position.y), 20, 40, 12, LIGHTGRAY);
            DrawText(TextFormat("Camera Zoom: %2.0f", camera.zoom), 20, 50, 12, LIGHTGRAY);
            DrawText(TextFormat("Camera Target: (%2.0f, %2.0f)", camera.target.x, camera.target.y), 20, 60, 12, LIGHTGRAY);
            DrawText(TextFormat("Player Health: %f", player.life), 20, 80, 12, LIGHTGRAY);
            DrawText(TextFormat("Player Temp: %f", player.temperature), 20, 90, 12, LIGHTGRAY);
            DrawText(TextFormat("Player Shards: %i", player.shards), 20, 100, 12, LIGHTGRAY);
            DrawText(TextFormat("Player SIem: %d", player.selectedItem), 20, 110, 12, LIGHTGRAY);
        }

        //GUI
        drawInventoryGUI(&player);
        drawFrozenGui(&player);
        drawLifeGui(&player);
        // GUI SHARDS
        DrawCustomFont(TextFormat("%3d", player.shards), {170, 940}, 14, WHITE);
        shardsSheet.Draw(0, {220, 925});

        EndDrawing();
        }

        // MAIN MENU
        else if (MainMenuActive)
        {
            // UPDATE
            MenuCursor.stateON = 1;
            aSystem.UpdateMusic();
            // DRAWING
            BeginDrawing();
            ClearBackground(BLACK);
            Logo.Draw(0, {SCREEN_WIDTH / 2.0f - 1560 / 2.0f + 400, SCREEN_HEIGHT / 2.0f - 480 / 2.0f});
            BeginMode2D(MenuCamera);
            drawMainMenuBG(deltaTime);
            EndMode2D();

            // GUI
            // PLAYBUTTON
            playButton.Draw();

            if (playButton.IsClicked(GetMousePosition()))
            {
                playButton.index = 1;
                DrawCustomFont("START", {SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f + 80.0f}, 17, WHITE);
            } else playButton.index = 0;

            if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && playButton.IsClicked(GetMousePosition())) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
            {
                aSystem.PlayMusic(0);
                MainMenuActive = 0;
                CreditsScreenActive = 0;
                MainGameActive = 1;
            }
            // VERSION CODE
            DrawCustomFont(TextFormat("Version %s", gameVersion), { 30, SCREEN_HEIGHT - 30}, 17, WHITE);
            if (IsGamepadAvailable(MAIN_GAMEPAD)) {
                DrawCustomFont(TextFormat("Controller Connected: %s", GetGamepadName(MAIN_GAMEPAD)), {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30}, 12, WHITE);
            } 
            else 
            {
                DrawCustomFont("Controller Connected: None", {SCREEN_WIDTH - 700, SCREEN_HEIGHT - 30}, 12, WHITE);
            }
            MenuCursor.Draw(GetMousePosition());

            EndDrawing();
        }

        else if (CreditsScreenActive)
        {
            // UPDATE
            MenuCursor.stateON = 1;
            aSystem.UpdateMusic();

            // DRAWING
            BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(MenuCamera);
            drawMainCreditsBG(deltaTime);
            EndMode2D();

            // VERSION CODE
            if (creditscouter >= 60 * 8) 
            {
                DrawCustomFont("Programming by Lukas Rennhofer", {SCREEN_WIDTH - 1200, SCREEN_HEIGHT / 2.0f - 400}, 17, WHITE);
    
            }
            if (creditscouter >= 60 * 9)
            {
                DrawCustomFont("Art by Moritz Rottensteiner", {SCREEN_WIDTH - 1200, SCREEN_HEIGHT / 2.0f - 300}, 17, WHITE);
            }
            if (creditscouter >= 60 * 10)
            {
                DrawCustomFont("Music by Timothy Kulig", {SCREEN_WIDTH - 1200, SCREEN_HEIGHT / 2.0f - 200}, 17, WHITE);
            }
            if (creditscouter >= 60 * 11)
            {
                DrawCustomFont("Inspiration from Celeste", {SCREEN_WIDTH - 1200, SCREEN_HEIGHT / 2.0f - 100}, 17, WHITE);
            }
            if (creditscouter >= 60 * 12)
            {
                DrawCustomFont("THANKS FOR PLAYING :)", {SCREEN_WIDTH - 1200, SCREEN_HEIGHT / 2.0f}, 17, WHITE);
            }

            //DrawCustomFont(TextFormat("Version %s", gameVersion), {30, SCREEN_HEIGHT - 30}, 17, WHITE);
            MenuCursor.Draw(GetMousePosition());
            creditscouter += 1;
            EndDrawing();
        }
        else if (KillScreenActive) {
            // UPDATE
            MenuCursor.stateON = 1;
            aSystem.UpdateMusic();

            // DRAWING
            BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(MenuCamera);
            drawKillScreenBG(deltaTime);
            EndMode2D();
            //GUI
            if (player.dieState == 0)
            {
                DrawCustomFont("FALLEN TO DEATH", {SCREEN_WIDTH - 1250, SCREEN_HEIGHT / 2.0f - 400}, 34, WHITE);
                DrawCustomFont("TIPP: USE THE DASH", {SCREEN_WIDTH - 1300, SCREEN_HEIGHT / 2.0f + 400}, 34, WHITE);
            } else if (player.dieState == 1)
            {
                DrawCustomFont("FROZEN TO DEATH", {SCREEN_WIDTH - 1250, SCREEN_HEIGHT / 2.0f - 400}, 34, WHITE);
                DrawCustomFont("TIPP: WARM YOURSELF WITH TORCHES", {SCREEN_WIDTH - 1550, SCREEN_HEIGHT / 2.0f + 400}, 34, WHITE);
            }
            // PLAYBUTTON
            retryButton.Draw();
            if (retryButton.IsClicked(GetMousePosition()))
            {
                retryButton.index = 1;
                DrawCustomFont("RETRY", {SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f - 230.0f}, 17, WHITE);
            }
            else
                retryButton.index = 0;
            if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && retryButton.IsClicked(GetMousePosition())) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
            {
                aSystem.PlayMusic(0);
                KillScreenActive = 0;
                MainGameActive = 1;
                firstZoom = 0;
                player.isControllable = 0;
                camera.zoom = 5.0f;
                framecounter = 0;
            }
            MenuCursor.Draw(GetMousePosition());
            EndDrawing();
        }
    }

    aSystem.UnloadMusic();
    aSystem.UnloadSounds();
    CloseWindow();

    return 0;
}

