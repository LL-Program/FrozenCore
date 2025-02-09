#include "../../raylib.h"
#include "../../raymath.h"
#include "player.hpp"

void UpdatePlayer(Player *player, std::vector<EnvItem> envItems, int envItemsLength, float delta)
{
    if (!player->init) {
       player->initPositon = player->position;
       player->init = 1; 
       player->lastPosition = player->initPositon;
    }
    player->playerIsHeated = 0;
    Vector2 oldPosition = player->position;
    static float velocity = 0.0f;
    const float acceleration = 2000.0f;
    const float deceleration = 200.0f;
    float maxSpeed = PLAYER_HOR_SPD;
    float frameSpeedAnimation_walking = 8.0f;
    bool moving = false;
    float slipperyFactor = 2.0f; // SLIPPERY EFFECT

    // Dash mechanic variables
    static float dashTime = 0.0f;
    const float dashDuration = 0.6f; // Duration of the dash in seconds
    const float dashSpeed = 500.0f; // Speed during the dash
    static bool isDashing = false;
    static float dashCooldown = 2.0f;
    static float dashCooldownTimer = 0.0f;

    if (player->life <= 20) 
    {
        player->position = player->initPositon;
        player->life = 100.0f;
    }
    if (player->isControllable) 
    {
        if (dashCooldownTimer > 0.0f)
        {
            dashCooldownTimer -= delta; // Reduce the cooldown timer
        }

        if (player->isSnowStorm)
            player->temperature -= 2 / 60; // -2 Temp. pro Sekunde

        if (!player->playerIsHeated)
        {
            player->temperature -= 1.5 / 60;
        }

        if (player->temperature <= 20)
        {
            player->life  = 0;  // DEATH BY TEMP
            player->dieState = 1;
            player->temperature = 60; // RESET TEMP
        }

        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) && dashCooldownTimer <= 0.0f && !isDashing)
        {
            isDashing = true;
            dashTime = 0.0f; 
            dashCooldownTimer = dashCooldown;

        }

        if (isDashing)
        {
            if ((player->lastState == PlayerState::WALKINGLEFT || player->lastState == PlayerState::IDLELEFT)  && player->currentState != PlayerState::DASHLEFT)
                player->currentState = PlayerState::DASHLEFT;
            else if ((player->lastState == PlayerState::WALKINGRIGHT || player->lastState == PlayerState::IDLERIGHT) && player->currentState != PlayerState::DASHRIGHT)
                player->currentState = PlayerState::DASHRIGHT;
            if (dashTime < dashDuration)
            {
                dashTime += delta;
                velocity = (velocity > 0) ? dashSpeed : -dashSpeed;
            }
            else
            {
                isDashing = false;
                if (player->currentState = PlayerState::DASHLEFT)
                    player->currentState = PlayerState::IDLELEFT;
                else if (player->currentState = PlayerState::DASHRIGHT)
                    player->currentState = PlayerState::IDLERIGHT;
            }
        }
        else if (IsKeyDown(KEY_A))
        {
            if (player->isSnowStorm && player->SnowStormSpawnLeft)
            {
                maxSpeed = PLAYER_SNOW_STORM_AGAINST_W_SPD;
                frameSpeedAnimation_walking = PLAYER_SNOW_STORM_AGAINST_A_SPD;
            }
            velocity -= acceleration * delta;
            if (velocity < -maxSpeed)
                velocity = -maxSpeed;
            player->lastState = player->currentState;
            player->currentState = PlayerState::WALKINGLEFT;
            moving = true;
        }
        else if (IsKeyDown(KEY_D))
        {
            if (player->isSnowStorm && !player->SnowStormSpawnLeft)
            {
                maxSpeed = PLAYER_SNOW_STORM_AGAINST_W_SPD;
                frameSpeedAnimation_walking = PLAYER_SNOW_STORM_AGAINST_A_SPD;
            }
            velocity += acceleration * delta;
            if (velocity > maxSpeed)
                velocity = maxSpeed;
            player->lastState = player->currentState;
            player->currentState = PlayerState::WALKINGRIGHT;
            moving = true;
        }
        else if (IsKeyDown(KEY_Q))
        {
        player->isIceModeOn = 1;
        }
        else if (IsGamepadAvailable(MAIN_GAMEPAD))
        {
            if (GetGamepadAxisMovement(MAIN_GAMEPAD, GAMEPAD_AXIS_LEFT_X) == -1.0f)
            {
                // PATCHED 1.1.0
                if (player->isSnowStorm && player->SnowStormSpawnLeft)
                {
                    maxSpeed = PLAYER_SNOW_STORM_AGAINST_W_SPD;
                    frameSpeedAnimation_walking = PLAYER_SNOW_STORM_AGAINST_A_SPD;
                }
                velocity -= acceleration * delta;
                if (velocity < -maxSpeed)
                    velocity = -maxSpeed;
                player->lastState = player->currentState;
                player->currentState = PlayerState::WALKINGLEFT;
                moving = true;
            }
            else if (GetGamepadAxisMovement(MAIN_GAMEPAD, GAMEPAD_AXIS_LEFT_X) == 1.0f)
            {
                // PATCHED 1.1.0
                if (player->isSnowStorm && !player->SnowStormSpawnLeft)
                {
                    maxSpeed = PLAYER_SNOW_STORM_AGAINST_W_SPD;
                    frameSpeedAnimation_walking = PLAYER_SNOW_STORM_AGAINST_A_SPD;
                }

                velocity += acceleration * delta;
                if (velocity > maxSpeed)
                    velocity = maxSpeed;
                player->lastState = player->currentState;
                player->currentState = PlayerState::WALKINGRIGHT;
                moving = true;
            }
            else if (IsGamepadButtonPressed(MAIN_GAMEPAD, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
            {
                player->isIceModeOn = 1;
            }
            else
            {
                if (velocity > 0)
                {
                    velocity -= deceleration * delta;
                    if (velocity < 0)
                        velocity = 0;
                }
                else if (velocity < 0)
                {
                    velocity += deceleration * delta;
                    if (velocity > 0)
                        velocity = 0;
                }
            }
        }
        else
        {
            if (velocity > 0)
            {
                velocity -= deceleration * slipperyFactor * delta;
                if (velocity < 0)
                    velocity = 0;
            }
            else if (velocity < 0)
            {
                velocity += deceleration * slipperyFactor * delta;
                if (velocity > 0)
                    velocity = 0;
            }
        }

        }


        player->position.x += velocity * delta;
        
        if (!moving)
        {
            if (player->lastState == PlayerState::WALKINGLEFT && player->currentState != PlayerState::IDLELEFT)
                player->currentState = PlayerState::IDLELEFT;
            else if (player->lastState == PlayerState::WALKINGRIGHT && player->currentState != PlayerState::IDLERIGHT)
                player->currentState = PlayerState::IDLERIGHT;
        }

        Rectangle playerRect = {player->position.x - 24, player->position.y - 96, 48.0f, 96.0f};

        for (int i = 0; i < envItemsLength; i++)
        {
            EnvItem *ei = envItems.data() + i;

            if (ei->blocking && CheckCollisionRecs(playerRect, ei->rect))
            {
                if (player->position.x > oldPosition.x)
                        player->position.x = ei->rect.x - 24;
                else if (player->position.x < oldPosition.x)
                    player->position.x = ei->rect.x + ei->rect.width + 24;

                break;
            }
        }

        if (!player->canJump)
        {
            player->speed += G * delta;
        }
        player->position.y += player->speed * delta;

        playerRect = Rectangle{player->position.x - 24, player->position.y - 96, 48.0f, 96.0f};
        bool isOnGround = false;
        for (int i = 0; i < envItemsLength; i++)
        {
                EnvItem *ei = envItems.data() + i;

                if (ei->blocking && CheckCollisionRecs(playerRect, ei->rect))
                {
                    if (player->speed > 0)
                    {
                        player->position.y = ei->rect.y;
                        player->speed = 0;
                        player->canJump = true;
                        isOnGround = true;
                    }
                    else if (player->speed < 0)
                    {
                        player->position.y = ei->rect.y + ei->rect.height + 96;
                        player->speed = 0;
                    }

                    break;
                }
            }

            if (!isOnGround)
            {
                player->canJump = false;
            }

            static float jumpHoldTime = 0;
            const float maxJumpForce = 30.0f;
            const float jumpIncreaseRate = 10.0f;
            const float maxHoldDuration = 5.0f;
            if (player->isControllable)
            {
                if (IsKeyDown(KEY_SPACE) && player->canJump || IsGamepadButtonDown(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && player->canJump)
                {
                    jumpHoldTime += delta;
                    if (jumpHoldTime > maxHoldDuration)
                        jumpHoldTime = maxHoldDuration;

                    float jumpForce = -PLAYER_JUMP_SPD + (jumpHoldTime * jumpIncreaseRate);
                    player->speed = fminf(jumpForce, -maxJumpForce);
                    player->canJump = false;
                }
                else if (IsKeyReleased(KEY_SPACE) || IsGamepadButtonReleased(MAIN_GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
                {
                    jumpHoldTime = 0;
                }
            }
            if (player->position.y > GetScreenHeight())
            {
                player->speed = 0;
                player->position = player->lastPosition;
                player->dieState = 0;
                player->life -= 30;
            }

            if (player->currentState != player->lastState)
            {
                if (!(player->lastState == PlayerState::IDLELEFT && player->currentState == PlayerState::IDLELEFT) &&
                    !(player->lastState == PlayerState::IDLERIGHT && player->currentState == PlayerState::IDLERIGHT))
                {
                    switch (player->currentState)
                    {
                    case PlayerState::WALKINGLEFT:
                        player->currentAnimation = Animation(player->sheet, 4, 9, frameSpeedAnimation_walking, true);
                        break;
                    case PlayerState::WALKINGRIGHT:
                        player->currentAnimation = Animation(player->sheet, 31, 36, frameSpeedAnimation_walking, true);
                        break;
                    case PlayerState::IDLELEFT:
                        player->currentAnimation = Animation(player->sheet, 0, 3, 4.0f, true);
                        break;
                    case PlayerState::IDLERIGHT:
                        player->currentAnimation = Animation(player->sheet, 27, 30, 4.0f, true);
                        break;
                    case PlayerState::DASHLEFT:
                        player->currentAnimation = Animation(&playerDash, 6, 11, 7.0f, false);
                        break;
                    case PlayerState::DASHRIGHT:
                        player->currentAnimation = Animation(&playerDash, 0, 5, 7.0f, false);
                        break;
                    }
                }

                player->lastState = player->currentState;
            }
            player->currentAnimation.Update(delta);
        }

void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = Vector2{width / 2.0f, height / 2.0f};
    camera->target = player->position;
}

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = Vector2{width / 2.0f, height / 2.0f};
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D(Vector2{maxX, maxY}, *camera);
    Vector2 min = GetWorldToScreen2D(Vector2{minX, minY}, *camera);

    if (max.x < width)
        camera->offset.x = width - (max.x - width / 2);
    if (max.y < height)
        camera->offset.y = height - (max.y - height / 2);
    if (min.x > 0)
        camera->offset.x = width / 2 - min.x;
    if (min.y > 0)
        camera->offset.y = height / 2 - min.y;
}

void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = Vector2{width / 2.0f, height / 2.0f};
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length));
    }
}

void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset = Vector2{width / 2.0f, height / 2.0f};
    camera->target.x = player->position.x;

    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed * delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera->target.y -= evenOutSpeed * delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->position.y;
        }
    }
}

void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    static Vector2 bbox = {0.2f, 0.2f};

    Vector2 bboxWorldMin = GetScreenToWorld2D(Vector2{(1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height}, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D(Vector2{(1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height}, *camera);
    camera->offset = Vector2{(1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height};

    if (player->position.x < bboxWorldMin.x)
        camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y)
        camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x)
        camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y)
        camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}

void DrawPlayer(Player* player, int delta)
{
    player->currentAnimation.Draw({player->position.x - 24, player->position.y - 92});
}
