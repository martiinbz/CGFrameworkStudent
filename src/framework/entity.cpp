#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"




 Entity::Entity() {

}
Entity::Entity(Mesh mesh1, Matrix44 matrix1) {

	mesh = mesh1;
	matrix = matrix1;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    // Get the vertices of the mesh
    const std::vector<Vector3>& meshVertices = mesh.GetVertices();

    // Iterate through each vertex
    for (size_t i = 0; i < meshVertices.size(); i += 3) {
        // Get the vertices of the current triangle
        Vector3 v0 = meshVertices[i];
        Vector3 v1 = meshVertices[i + 1];
        Vector3 v2 = meshVertices[i + 2];

        // Transform vertices to world space using the model matrix
        v0 = matrix* v0;
        v1 = matrix * v1;
        v2 = matrix * v2;

        // Project vertices to clip space using the camera
        bool negZ0, negZ1, negZ2;
        Vector3 clipSpaceV0 = camera->ProjectVector(v0, negZ0);
        Vector3 clipSpaceV1 = camera->ProjectVector(v1, negZ1);
        Vector3 clipSpaceV2 = camera->ProjectVector(v2, negZ2);

        // Check if any of the vertices is outside the camera frustum
        if (negZ0 || negZ1 || negZ2) {
            // Discard the whole triangle if any vertex is outside the frustum
            continue;
        }

        // Convert clip space positions to screen space using framebuffer width and height
        int screenWidth = framebuffer->width;
        int screenHeight = framebuffer->height;

        Vector2 screenSpaceV0 = Vector2(
            (clipSpaceV0.x + 1.0f) * 0.5f * screenWidth,
            (1.0f - (clipSpaceV0.y + 1.0f) * 0.5f) * screenHeight
        );

        Vector2 screenSpaceV1 = Vector2(
            (clipSpaceV1.x + 1.0f) * 0.5f * screenWidth,
            (1.0f - (clipSpaceV1.y + 1.0f) * 0.5f) * screenHeight
        );

        Vector2 screenSpaceV2 = Vector2(
            (clipSpaceV2.x + 1.0f) * 0.5f * screenWidth,
            (1.0f - (clipSpaceV2.y + 1.0f) * 0.5f) * screenHeight
        );

        // Draw the wireframe of the triangle using DDA algorithm
        framebuffer->DrawLineDDA(screenSpaceV0.x, screenSpaceV0.y, screenSpaceV1.x, screenSpaceV1.y, c);
        framebuffer->DrawLineDDA(screenSpaceV1.x, screenSpaceV1.y, screenSpaceV2.x, screenSpaceV2.y, c);
        framebuffer->DrawLineDDA(screenSpaceV2.x, screenSpaceV2.y, screenSpaceV0.x, screenSpaceV0.y, c);
    }
}