#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"




Entity::Entity() {

}
Entity::Entity(Mesh& mesh1, Matrix44& rotationmatrix,Matrix44& translationmatrix) {

	mesh = mesh1;
    modelmatrix = translationmatrix*rotationmatrix;
   
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    //obtenemos los vertices
    const std::vector<Vector3>& meshVertices = mesh.GetVertices();

    //iteramos
    for (int i = 0; i < meshVertices.size(); i += 3) {
        //obtenemos los vertices de cada triangulo
        Vector3 v0 = meshVertices[i];
        Vector3 v1 = meshVertices[i + 1];
        Vector3 v2 = meshVertices[i + 2];

        //Transformamos a world space
        v0 = modelmatrix* v0;
        v1 = modelmatrix* v1;
        v2 = modelmatrix* v2;

        // Proyectamos con la camara para ver si los puntos están dentro de su campo de vision
        bool negZ0, negZ1, negZ2;
        Vector3 clipSpaceV0 = camera->ProjectVector(v0, negZ0);
        Vector3 clipSpaceV1 = camera->ProjectVector(v1, negZ1);
        Vector3 clipSpaceV2 = camera->ProjectVector(v2, negZ2);

        //miramos si alguno de los vertices se sale de la camara
        if (negZ0 || negZ1 || negZ2) {
           //lo descartamos
            continue;
        }

         //ajustamos la posicion a la del framebuffer ( de clipspace a screenspace ( de [-1,1] a [0,1])
        int screenWidth = framebuffer->width;
        int screenHeight = framebuffer->height;

        
        Vector2 screenSpaceV0 = Vector2((((clipSpaceV0.x + 1.0f) * screenWidth) / 2), (((clipSpaceV0.y + 1.0f) * screenHeight) / 2));
        Vector2 screenSpaceV1 = Vector2((((clipSpaceV1.x + 1.0f) * screenWidth) / 2), (((clipSpaceV1.y + 1.0f) * screenHeight) / 2));
        Vector2 screenSpaceV2 = Vector2((((clipSpaceV2.x + 1.0f) * screenWidth) / 2), (((clipSpaceV2.y + 1.0f) * screenHeight) / 2));

        //vamos dibujando los triangulos ppor pantalla
        
        framebuffer->DrawLineDDA(screenSpaceV0.x, screenSpaceV0.y, screenSpaceV1.x, screenSpaceV1.y, c);
        framebuffer->DrawLineDDA(screenSpaceV1.x, screenSpaceV1.y, screenSpaceV2.x, screenSpaceV2.y, c);
        framebuffer->DrawLineDDA(screenSpaceV2.x, screenSpaceV2.y, screenSpaceV0.x, screenSpaceV0.y, c);
        
        

       
        /*
        std::cout << "Segundo VECTOR y " << screenSpaceV0.y << std::endl;
        std::cout << "Segundo VECTOR x " << screenSpaceV1.x << std::endl;
        std::cout << "Tercer VECTOR x " << screenSpaceV2.x << std::endl;
        std::cout << "Terccer VECTOR y " << screenSpaceV1.y << std::endl;*/
    }
}
void Entity::Update(float seconds_elapsed) {
      //translationmatrix.SetTranslation(0, 0, 0.04);
    modelmatrix.Rotate((DEG2RAD * 45) * seconds_elapsed, { 0,1,0 });
    
}