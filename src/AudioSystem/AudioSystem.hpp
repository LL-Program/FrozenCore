#pragma once

#include "../../raylib.h"
#include "../../raymath.h"
#include <unordered_map>
#include <vector>
#include <string>

class AudioSystem
{
public:
    AudioSystem();
    ~AudioSystem();

    // ================= MUSIC SYSTEM ==================
    void LoadMusic(const std::string &filePath);
    void PlayMusic(int trackIndex);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    void UpdateMusic();
    void SetMusicVolumeCustom(float volume);
    void UnloadMusic();

    // ================= POSITIONAL SOUND SYSTEM ==================
    void LoadSoundEffect(const std::string &soundName, const std::string &filePath);
    void PlaySoundEffect(const std::string &soundName, Vector2 soundPosition, Vector2 listenerPosition, bool loop);
    void SetGlobalSoundVolumeCustom(float volume);
    void UnloadSounds();

private:
    struct PositionalSound
    {
        Sound sound;
        Vector2 position;
    };

    std::vector<Music> musicBank;
    Music *currentMusic;
    float musicVolume;
    float soundVolume;
    std::unordered_map<std::string, PositionalSound> soundEffects;

    float GetDistanceAttenuation(float distance);
    float GetStereoPan(Vector2 soundPosition, Vector2 listenerPosition, float maxPanDistance);
};
