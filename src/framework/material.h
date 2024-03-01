#pragma once
#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"
#include "shader.h"

class Material {

private:
	Shader* shader;
	Texture texture;
	Color color;
	

	struct sLight {
		Vector3 position;
		float diffuse_intensity;
		float specular_intensity;
	};



public:
	Material();
	Material::Material(Shader* shader1, Texture texture1, Color color1);
	void Material::Enable();
	void Material::Disable();



};

