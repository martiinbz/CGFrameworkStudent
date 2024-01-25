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

public:
    void Init() {
        for (int i = 0; i < MAX_PARTICLES; ++i) {
            particles[i].position.Random(1280); // Assuming your window size is 800x600, adjust as needed
            particles[i].position.Random(700);
            particles[i].velocity.Random(2.0f);   // Adjust as needed
            particles[i].color = Color::WHITE;
            particles[i].acceleration = 0.1f;     // Adjust as needed
            particles[i].ttl = static_cast<float>(rand() % 100) / 10.0f; // Adjust as needed
            particles[i].inactive = false;
        }
    }

 
    void Update(float dt) {
        for (int i = 0; i < MAX_PARTICLES; ++i) {
            if (!particles[i].inactive) {
                particles[i].position = particles[i].position + particles[i].velocity * dt;
                particles[i].ttl -= dt;

                // Check if particle has expired
                if (particles[i].ttl <= 0.0f) {
                    particles[i].inactive = true;
                }
            }
        }
    }
};

