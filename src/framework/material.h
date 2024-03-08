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
	Material* material;
	int scene_lights;
};

class Material {

private:
	Shader* shader;
	Texture* texture;
	Color color;

public:
	Material();
	Material(Shader* shader1, Texture *texture1, Color color1);
    void Material::Enable(  const sUniformData &uniformData);
	void Material::Disable();
};




