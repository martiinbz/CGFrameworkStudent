#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"




void Entity::entity() {

}
void Entity::entity(Mesh mesh1, Matrix44 matrix1) {

	mesh = mesh1;
	matrix = matrix1;
}
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c){


}