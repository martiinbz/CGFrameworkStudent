#pragma once
#include "image.h"
#include "mesh.h"
#include "framework.h"
#include "entity.h"

class Entity {

private:
	Mesh mesh;
	Matrix44 matrix;


public: 
	void entity();
	void entity(Mesh mesh, Matrix44 matrix);
	void Render(Image* framebuffer, Camera* camera, const Color& c);



};