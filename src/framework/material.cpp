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
void Material::Enable(const sUniformData& uniformData) {
	shader->SetMatrix44("u_model", uniformData.modelmatrix);
	shader->Enable();
}
void Material::Disable() {
	shader->Disable();
}