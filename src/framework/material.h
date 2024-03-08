#pragma once

#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"
#include "shader.h"
#include "material.h"
#include "texture.h"
class Material;

struct sLight {
	Vector3 position;
	float diffuse_intensity;
	float specular_intensity;
};

struct sUniformData {
	Matrix44 modelmatrix;
	Matrix44 viewprojectionmatrix;
	float intensity;

	int scene_lights;
};

class Material {

private:
	

public:
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Color color;
	Material();
	Material(Shader* shader1, Texture* texture1, Color color1,Mesh m);
    void Material::Enable(  const sUniformData &uniformData);
	void Material::Disable();
};




