#include "../../raylib.h"
#include <stdlib.h>
#include "particles.hpp"
#include "../Utils/constants.hpp"

void SpawnParticles(Particle *particles, int *particleCount, Vector2 spawnPoint)
{
    if (*particleCount < PARTICLES_MAX)
    {
        Particle *particle = &particles[*particleCount];
        particle->position = spawnPoint;
        particle->speed = Vector2{(float)(rand() % 10 - 5), (float)(rand() % 10 - 5)};
        particle->active = true;
        (*particleCount)++;
    }
}

void UpdateParticles(Particle *particles, int *particleCount, float deltaTime)
{
    for (int i = 0; i < *particleCount; i++)
    {
        Particle *particle = &particles[i];

        if (particle->active)
        {
            particle->position.x += particle->speed.x * deltaTime;
            particle->position.y -= particle->speed.y * deltaTime;

            particle->speed.y += 20.0f * deltaTime;

            if (particle->position.y < PARTICLE_DESTROY_HEIGHT || particle->position.x < 0 || particle->position.x > SCREEN_WIDTH)
            {
                particle->active = false;
            }
        }
    }
}

void DrawParticles(Particle *particles, int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        if (particles[i].active)
        {
            DrawRectangleV(particles[i].position, Vector2{PARTICLE_PIXEL_SIZE, PARTICLE_PIXEL_SIZE}, WHITE);
        }
    }
}

void SpawnSnowParticles(Particle *particles, int *particleCount, Vector2 spawnPoint)
{
    if (*particleCount < PARTICLES_MAX)
    {
        Particle *particle = &particles[*particleCount];
        particle->position = spawnPoint;

        particle->speed = Vector2{(float)(rand() % 3 - 1), (float)(rand() % 5 + 2)};
        particle->active = true;
        (*particleCount)++;
    }
}

void UpdateSnowParticles(Particle *particles, int *particleCount, float deltaTime)
{
    for (int i = 0; i < *particleCount; i++)
    {
        Particle *particle = &particles[i];

        if (particle->active)
        {
            particle->position.x += particle->speed.x * deltaTime;
            particle->position.y += particle->speed.y * deltaTime;

            particle->speed.y += 10.0f * deltaTime;

            if (particle->position.y > SCREEN_HEIGHT || particle->position.x < 0 || particle->position.x > SCREEN_WIDTH)
            {
                particle->position = Vector2{(float)(rand() % SCREEN_WIDTH), 0.0f};
                particle->speed = Vector2{(float)(rand() % 3 - 1), (float)(rand() % 5 + 2)};
            }
        }
    }
}

void DrawSnowParticles(Particle *particles, int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        if (particles[i].active)
        {
            DrawRectangleV(particles[i].position, Vector2{PARTICLE_PIXEL_SIZE, PARTICLE_PIXEL_SIZE}, WHITE);
        }
    }
}

void SpawnSnowStormParticles(Particle *particles, int *particleCount, bool spawnFromLeft)
{
    if (*particleCount < PARTICLES_MAX)
    {
        Particle *particle = &particles[*particleCount];


        particle->position.x = spawnFromLeft ? -10.0f : SCREEN_WIDTH + 10.0f;
        particle->position.y = (float)(rand() % SCREEN_HEIGHT);

        float direction = spawnFromLeft ? 1.0f : -1.0f;
        particle->speed = Vector2{SNOWSTORM_SPEED * direction + (float)(rand() % 20 - 10), (float)(rand() % 5 + 2)};

        particle->active = true;
        (*particleCount)++;
    }
}

void UpdateSnowStormParticles(Particle *particles, int *particleCount, float deltaTime)
{
    for (int i = 0; i < *particleCount; i++)
    {
        Particle *particle = &particles[i];

        if (particle->active)
        {
            particle->position.x += particle->speed.x * deltaTime;
            particle->position.y += particle->speed.y * deltaTime;


            particle->speed.y += 10.0f * deltaTime;

            if (particle->position.x < -10 || particle->position.x > SCREEN_WIDTH + 10)
            {
                particle->position.x = (particle->position.x < 0) ? SCREEN_WIDTH + 10 : -10;
                particle->position.y = (float)(rand() % SCREEN_HEIGHT);
                particle->speed = Vector2{SNOWSTORM_SPEED * (particle->position.x < 0 ? 1.0f : -1.0f) + (float)(rand() % 20 - 10), (float)(rand() % 5 + 2)};
            }

            if (particle->position.y > SCREEN_HEIGHT)
            {
                particle->position.y = 0;
            }
        }
    }
}

void DrawSnowStormParticles(Particle *particles, int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        if (particles[i].active)
        {
            DrawRectangleV(particles[i].position, Vector2{PARTICLE_PIXEL_SIZE, PARTICLE_PIXEL_SIZE}, WHITE);
        }
    }
}

void ResetSnowstorm(Particle *particles, int *particleCount)
{
    *particleCount = 0;
}
