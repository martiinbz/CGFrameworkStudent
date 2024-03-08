#pragma once
#include "image.h"
#include "mesh.h"
#include "framework.h"
#include "entity.h"
#include "shader.h"
#include "material.h"

class Entity {

private:
	Mesh* mesh;
	
	Matrix44 rotationmatrix;
	Matrix44 translationmatrix;
	Matrix44 modelmatrix;
	Material material;
	
	
	
public: 
	
	Entity();
	Entity(Mesh* mesh, Matrix44& rotationmatrix, Matrix44& translationmatrix,Material m);
	void Entity::Render(sUniformData uniformData);

	Matrix44 Entity::GetModelMatrix();

	void Entity::Update(float seconds_elapsed);



};