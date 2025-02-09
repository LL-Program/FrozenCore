#pragma once

#include "../../raylib.h"

typedef struct Particle
{
    Vector2 position;
    Vector2 speed;
    bool active;
} Particle;

void SpawnParticles(Particle *particles, int *particleCount, Vector2 spawnPoint);
void UpdateParticles(Particle *particles, int *particleCount, float deltaTime);
void DrawParticles(Particle *particles, int particleCount);

// SNOW
void SpawnSnowParticles(Particle *particles, int *particleCount, Vector2 spawnPoint);
void UpdateSnowParticles(Particle *particles, int *particleCount, float deltaTime);
void DrawSnowParticles(Particle *particles, int particleCount);

// SNOW STORM

void SpawnSnowStormParticles(Particle *particles, int *particleCount, bool spawnFromLeft);
void UpdateSnowStormParticles(Particle *particles, int *particleCount, float deltaTime);
void DrawSnowStormParticles(Particle *particles, int particleCount);
void ResetSnowstorm(Particle *particles, int *particleCount);