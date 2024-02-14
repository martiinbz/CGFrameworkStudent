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
	Image texture;


public: 
	Entity();
	Entity(Mesh& mesh, Matrix44& rotationmatrix, Matrix44& translationmatrix,Image& texture1);
	void Entity::Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer, bool texture, bool inter);
	void Entity::Update(float seconds_elapsed);



};