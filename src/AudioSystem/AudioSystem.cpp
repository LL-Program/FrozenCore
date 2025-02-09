#include "raymath.h"
#include "AudioSystem.hpp"
#include <cmath>

AudioSystem::AudioSystem() : currentMusic(nullptr), musicVolume(1.0f), soundVolume(1.0f)
{
    InitAudioDevice();
}

AudioSystem::~AudioSystem()
{
    UnloadMusic();
    UnloadSounds();
    CloseAudioDevice();
}

// ================= MUSIC SYSTEM ==================

void AudioSystem::LoadMusic(const std::string &filePath)
{
    Music newMusic = LoadMusicStream(filePath.c_str());
    musicBank.push_back(newMusic);
}

void AudioSystem::PlayMusic(int trackIndex)
{
    if (trackIndex >= 0 && trackIndex < musicBank.size())
    {
        if (currentMusic)
            StopMusic();
        currentMusic = &musicBank[trackIndex];
        PlayMusicStream(*currentMusic);
        SetMusicVolume(*currentMusic, musicVolume);
    }
}

void AudioSystem::StopMusic()
{
    if (currentMusic)
    {
        StopMusicStream(*currentMusic);
        currentMusic = nullptr;
    }
}

void AudioSystem::PauseMusic()
{
    if (currentMusic)
        PauseMusicStream(*currentMusic);
}

void AudioSystem::ResumeMusic()
{
    if (currentMusic)
        ResumeMusicStream(*currentMusic);
}

void AudioSystem::UpdateMusic()
{
    if (currentMusic)
        UpdateMusicStream(*currentMusic);
}

void AudioSystem::SetMusicVolumeCustom(float volume)
{
    musicVolume = volume;
    if (currentMusic)
    {
        SetMusicVolume(*currentMusic, musicVolume);
    }
}

void AudioSystem::UnloadMusic()
{
    for (Music &music : musicBank)
    {
        UnloadMusicStream(music);
    }
    musicBank.clear();
}

// ================= POSITIONAL SOUND SYSTEM ==================

void AudioSystem::LoadSoundEffect(const std::string &soundName, const std::string &filePath)
{
    PositionalSound newSound;
    newSound.sound = LoadSound(filePath.c_str());
    newSound.position = {0, 0};
    soundEffects[soundName] = newSound;
}

void AudioSystem::PlaySoundEffect(const std::string &soundName, Vector2 soundPosition, Vector2 listenerPosition, bool loop)
{
    if (soundEffects.find(soundName) == soundEffects.end())
        return;

    Sound sound = soundEffects[soundName].sound;

    float distance = Vector2Distance(listenerPosition, soundPosition);
    float volume = GetDistanceAttenuation(distance) * soundVolume;
    float pan = GetStereoPan(soundPosition, listenerPosition, 500.0f);

    SetSoundVolume(sound, volume);
    SetSoundPan(sound, pan);

    if (loop)
    {
        if (!IsSoundPlaying(sound))
        {
            PlaySound(sound);
        }
    }
    else
    {
        PlaySound(sound);
    }
}

void AudioSystem::SetGlobalSoundVolumeCustom(float volume)
{
    soundVolume = volume;
}

void AudioSystem::UnloadSounds()
{
    for (auto &sound : soundEffects)
    {
        UnloadSound(sound.second.sound);
    }
    soundEffects.clear();
}

// ================= AUDIO POSITIONING HELPERS ==================

float AudioSystem::GetDistanceAttenuation(float distance)
{
    float maxDistance = 500.0f;
    float minVolume = 0.1f; 

    float attenuation = 1.0f - (distance / maxDistance);
    return (attenuation > minVolume) ? attenuation : minVolume;
}

float AudioSystem::GetStereoPan(Vector2 soundPosition, Vector2 listenerPosition, float maxPanDistance)
{
    float pan = (soundPosition.x - listenerPosition.x) / maxPanDistance;

    if (pan > 1.0f)
        pan = -1.0f;
    if (pan < -1.0f)
        pan = 1.0f;

    return pan;
}
