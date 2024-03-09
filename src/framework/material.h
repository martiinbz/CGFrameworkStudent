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
	Vector3 diffuse_intensity;
	Vector3 specular_intensity;
};

struct sUniformData {
	Matrix44 modelmatrix;
	Matrix44 viewprojectionmatrix;
	Vector3 ambient_intensity;
	Vector3 eye_position;
	sLight scene_lights;
};

class Material {

private:
	

public:
	
	Shader* shader;
	Texture* texture;
	Vector3 Ka;
	Vector3 Kd;
	Vector3 Ks;
	float shininess;
	Color color;
	Material();
	Material(Shader* shader1, Texture* texture1, Color color1);
    void Material::Enable(  const sUniformData &uniformData);
	void Material::Disable();
};




