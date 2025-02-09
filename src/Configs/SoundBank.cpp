#include "SoundBank.hpp"

AudioSystem aSystem;

void InitSounds()
{
    // DEBUG SOUND
    aSystem.LoadSoundEffect("jump", "resources/sounds/jump.mp3");
    // SHOP GUARD LOOP
    aSystem.LoadSoundEffect("ShopGuardIdle", "resources/sounds/ShopGuard/Idle.mp3");
    // SHOP GUARD DOWN
    aSystem.LoadSoundEffect("ShopGuardDown", "resources/sounds/ShopGuard/Down.mp3");
    // CANCEL
    aSystem.LoadSoundEffect("Cancel", "resources/sounds/cancel.mp3");
}

void InitMusic()
{
    // MAIN LEVEL 1
    aSystem.LoadMusic("resources/music/Underground Lair.mp3");
    aSystem.LoadMusic("resources/music/Kill Screen.mp3");
    aSystem.LoadMusic("resources/music/Blip Bleep Bloop.mp3");
    aSystem.LoadMusic("resources/music/Pause Screen.mp3");
}