#pragma once

#include "../../raylib.h"
#include "../../raymath.h"
#include "envItem.hpp"
#include "../Utils/spriteSheet.hpp"
#include "../Utils/animation.hpp"
#include "../Utils/constants.hpp"
#include "../Configs/SpriteSheetBank.hpp"

typedef enum PlayerState
{
    IDLELEFT,
    IDLERIGHT,
    WALKINGLEFT,
    WALKINGRIGHT,
    FALLINGRIGHT,
    FALLINGLEFT,
    JUMPINGLEFT,
    JUMPINGRIGHT,
    WALLGLIDELEFT,
    WALLGLIDERIGHT,
    DASHLEFT,
    DASHRIGHT

}
PlayerState;
typedef struct Player
{
    Vector2 position;
    Vector2 initPositon;
    float speed;
    bool canJump;
    SpriteSheet* sheet;
    Animation currentAnimation;
    PlayerState currentState;
    PlayerState lastState;

    // LIFE
    float temperature = 60; // Standart
    float life = 100;
    bool playerIsHeated = 0;
    // SHARDS
    int shards = 0;
    int selectedItem = 0;
    // SNOWSTORM
    bool isSnowStorm = 0;
    bool SnowStormSpawnLeft = 0;
    //CONTROLLING
    bool isControllable = 0;
    bool init = 0;
    // ICE MODE
    bool isIceModeOn = 0;
    Vector2 IceModeCpos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    // TORCH POSITION
    Vector2 lastPosition = position;
    //FINISHED
    bool isFinished = 0;
    bool missionentried = 0;
    // DYING
    int dieState = 1; // 0 = Falling, 1 = Freezing, 2 = ICICLE?

    // INVENTORY
    std::vector<int> inventory[MAX_ITEMS];

    Player() {
        inventory->resize(9, -1);
    }

} Player;

void UpdatePlayer(Player *player, std::vector<EnvItem> envItems, int envItemsLength, float delta);
void DrawPlayer(Player *player, int delta);
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, int envItemsLength, float delta, int width, int height);
void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
