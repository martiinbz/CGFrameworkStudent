#pragma once
#include "image.h"
#include "mesh.h"
#include "framework.h"
#include "entity.h"

class Entity {

private:
	Mesh mesh;
	Matrix44 modelmatrix;
	Matrix44 rotationmatrix;
	Matrix44 translationmatrix;


public: 
	Entity();
	Entity(Mesh& mesh, Matrix44& rotationmatrix, Matrix44& translationmatrix);
	void Render(Image* framebuffer, Camera* camera, const Color& c);
	void Entity::Update(float seconds_elapsed);



};