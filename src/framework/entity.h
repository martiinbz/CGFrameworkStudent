#pragma once
#include "image.h"
#include "mesh.h"
#include "framework.h"
#include "entity.h"
#include "shader.h"

class Entity {

private:
	Mesh* mesh;
	
	Matrix44 rotationmatrix;
	Matrix44 translationmatrix;
	Texture texture;
	Matrix44 modelmatrix;
	Shader* shader;


public: 
	
	Entity();
	Entity(Mesh* mesh, Matrix44& rotationmatrix, Matrix44& translationmatrix,Texture texture1,Shader* shader1);
	void Entity::Render(Camera* camera);

	void Entity::Update(float seconds_elapsed);



};