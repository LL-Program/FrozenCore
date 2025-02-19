#pragma once

#include "../../raylib.h"

//DEBUG MODE
#define DEBUG_MODE_ON 0
//SCREEN
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS_LIMIT 60
//SPRITES
#define SCALE_FACTOR_CURSOR 4.0f
#define SCALE_FACTOR_8_8 6.0f
#define SCALE_FACTOR_16_16 3.0f
#define SCALE_FACTOR_32_32 1.5f
#define SPRITE_SIZE_16_16 (16.0f * SCALE_FACTOR_16_16)
#define SPRITES_16_32_Y_OFFSET 4.0f
//PARTICLES
#define PARTICLES_MAX 1500
#define PARTICLE_SPEED 50
#define PARTICLE_DESTROY_HEIGHT 100
#define PARTICLE_PIXEL_SIZE 3
#define SNOWSTORM_SPEED 450.0f
// PLAYER
#define G 900
#define PLAYER_JUMP_SPD 440.0f
#define PLAYER_HOR_SPD 200.0f
#define PLAYER_SNOW_STORM_AGAINST_W_SPD 50.0f
#define PLAYER_SNOW_STORM_AGAINST_A_SPD 4.0f
#define PLAYER_JUMP_SPD_INCREASE 100.0f
//FONT
#define DEBUG_FONT_SIZE 12f
//CONTROLLER
#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS "playstation"
#define MAIN_GAMEPAD 0
#define CONTROLLER_ICONS_SCALE_16_16 1.3f
//CONTROLLER BUTTONS
#define XBOX_A_BUTTON 0
#define XBOX_X_BUTTON 1
#define XBOX_B_BUTTON 2
#define XBOX_Y_BUTTON 3
#define XBOX_ACTION_SELECT_UP 8
#define XBOX_ACTION_SELECT_DOWN 8
#define XBOX_ACTION_SELECT_LEFT 10
#define XBOX_ACTION_SELECT_RIGHT 11
#define XBOX_ACTION_TRIGGER_RIGHT_DASH 7
// ITEMS
#define SCALE_FACTOR_ITEM_16_16 2.0f
#define ITEM_FONT_SIZE 12.0f
#define UP_DOWN_RATIO 30.0f
#define UP_DOWN_SPEED 6
#define ITEM_DETECTION_RANGE 125.0f
// KEYBOARD
#define KEYBOARD_ACTION_BUTTON_E 2
#define KEYBOARD_ACTION_SELECT_LEFT 55
#define KEYBOARD_ACTION_SELECT_RIGHT 56
#define KEYBOARD_ACTION_SELECT_UP 57
#define KEYBOARD_ACTION_SELECT_DOWN 58
#define KEYBOARD_SHIFT 46
// INVENTORY
#define MAX_ITEMS 9
// SHOP
#define SHOP_DETECTION_RANGE 175.0f
// ICICLE
#define ICICLE_FALL_SPD 400.0f
// GUI
#define SCALE_FACTOR_16_16_GUI_MENU 6.0f
// GUARD
#define GUARD_DETECTION_RANGE 175.0f
