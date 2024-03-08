#pragma once
#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"
#include "shader.h"
#include "material.h"


class Material {

private:
	Shader* shader;
	Texture* texture;
	Color color;



	
	
	

public:
	Material();
	Material(Shader* shader1, Texture* texture1, Color color1);
    void Enable(const sUniformData& uniformData);
	void Disable();
};
struct sLight {
	Vector3 position;
	float diffuse_intensity;
	float specular_intensity;
};

typedef struct {
	Matrix44 modelmatrix;
	Matrix44 viewprojectionmatrix;
	float intensity;
	Material* material;
	int scene_lights;
}sUniformData;


