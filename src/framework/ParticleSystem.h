#pragma once
#include "framework.h"

class ParticleSystem {
public:
    static const int MAX_PARTICLES = 100;

    struct Particle {
        Vector2 position;
        Vector2 velocity;
        Color color;
        float acceleration;
        float ttl;
        bool inactive;
    };

    Particle particles[MAX_PARTICLES];
};