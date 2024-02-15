#include "image.h"
#include "framework.h"
#include "mesh.h"
#include "application.h"
#include "entity.h"
#include "camera.h"




Entity::Entity() {

}
Entity::Entity(Mesh& mesh1, Matrix44& rotationmatrix,Matrix44& translationmatrix,Image& texture1) {

	mesh = mesh1;
    modelmatrix = translationmatrix*rotationmatrix;
    texture = texture1;
   
}

void Entity::Render(Image* framebuffer, Camera* camera,FloatImage* zBuffer,bool bool_texture, bool bool_interpolate,bool oclussion){
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

        
        Vector2 uv0 = mesh.GetUVs()[i];
        Vector2 uv1 = mesh.GetUVs()[i + 1];
        Vector2 uv2 = mesh.GetUVs()[i + 2];

        Vector3 vv0 = Vector3(static_cast<int>(screenSpaceV0.x), static_cast<int>(screenSpaceV0.y), static_cast<float>(clipSpaceV0.z));
        Vector3 vv1 = Vector3(static_cast<int>(screenSpaceV1.x), static_cast<int>(screenSpaceV1.y), static_cast<float>(clipSpaceV1.z));
        Vector3 vv2 = Vector3(static_cast<int>(screenSpaceV2.x), static_cast<int>(screenSpaceV2.y), static_cast<float>(clipSpaceV2.z));

        uv0.x = ((uv0.x + 1) * (screenWidth - 1)) / 2;
        uv0.y = (((uv0.y + 1) * (screenHeight - 1)) / 2);

        uv1.x = ((uv1.x + 1) * (screenWidth - 1)) / 2;
        uv1.y = (((uv1.y + 1) * (screenHeight - 1)) / 2);

        uv2.x = ((uv2.x + 1) * (screenWidth - 1)) / 2;
        uv2.y = (((uv2.y + 1) * (screenHeight - 1)) / 2);

        //vamos dibujando los triangulos ppor pantalla
        if (bool_texture == true) {
            
           framebuffer->DrawTriangleInterpolated(vv0, vv1, vv2, Color::RED, Color::GREEN, Color::BLUE, zBuffer,&texture,uv0,uv1,uv2,oclussion);
        }
        else if (bool_texture == false && bool_interpolate == true) {

            framebuffer->DrawTriangleInterpolated(vv0, vv1, vv2, Color::RED, Color::GREEN, Color::BLUE, zBuffer, nullptr, uv0, uv1, uv2,oclussion);
        }
        else {
            framebuffer->DrawTriangle(screenSpaceV0, screenSpaceV1, screenSpaceV2, Color::WHITE, true, Color::WHITE);

        }
        
       

       
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
enum class eRenderMode {
    POINTCLOUD,
    WIREFRAME,
    TRIANGLES,
    TRIANGLES_INTERPOLATED
};
eRenderMode mode;


