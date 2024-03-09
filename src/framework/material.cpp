#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"
#include "material.h"
#include "shader.h"





Material::Material() {


}
Material::Material(Shader* shader1, Texture* texture1, Color color1) {

	
	shader = shader1;
	texture = texture1;
	color = color1;
	
}


void Material::Enable( const sUniformData& uniformData) {
	
	glEnable(GL_DEPTH_TEST);
	shader->Enable();
	shader->SetMatrix44("u_model", uniformData.modelmatrix);
	shader->SetMatrix44("u_viewprojection", uniformData.viewprojectionmatrix);
	shader->SetTexture("lee", texture);
	shader->SetVector3("Ia", uniformData.ambient_intensity);
	shader->SetVector3("Imd", uniformData.scene_lights.diffuse_intensity);
	shader->SetVector3("Im,s", uniformData.scene_lights.specular_intensity);
	shader->SetVector3("m", uniformData.scene_lights.position);
	shader->SetVector3("Ka",Ka);
	shader->SetVector3("Ks", Ks);
	shader->SetVector3("Kd", Kd);
	shader->SetFloat("shininess", shininess);
	shader->SetVector3("u_eyePosition", uniformData.eye_position);
	
}

void Material::Disable() {
	shader->Disable();
}