#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "image.h"
#include "button.h"
#include "entity.h"




Application::Application(const char* caption, int width, int height)
{
    this->window = createWindow(caption, width, height);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    this->mouse_state = 0;
    this->time = 0.f;
    this->window_width = w;
    this->window_height = h;
    this->keystate = SDL_GetKeyboardState(nullptr);

    this->framebuffer.Resize(w, h);
    this->zbuffer.Resize(w, h);
    
    int start_x, start_y, start_z, end_x, end_y, end_z;
    int current_fov = 45;
    int current_near = 0.01;
    int current_far = 100;
    formulas = true;
    filters = false;
    transformation = false;
    mesh = false;
    subtask = 1;
    rotationmatrix.SetRotation(0,Vector3(0,0,0)); 
    translationmatrix.SetTranslation(0, 0, 0.0);
    
    camera1.LookAt(Vector3(0.5,0,0),Vector3(0,0,0),Vector3::UP);
    
   
  
	
}

Application::~Application()
{
	
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;

   
    lee = Texture::Get("textures/lee_color_specular.tga");
    
    simple.LoadOBJ("meshes/lee.obj");
   
    //creamos los shaders y la entidad
    shader1 = Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs");
    
    material = &Material(shader1, lee, Color(255, 0, 0));
    entity = Entity(&simple, rotationmatrix, translationmatrix, *material);
    
   
    
  
    uniformdata.viewprojectionmatrix = camera1.viewprojection_matrix;
    uniformdata.modelmatrix = entity.GetModelMatrix();
    uniformdata.material = material;
    


}


void Application::Render(void)
{
   
    
  
        
        entity.Render(uniformdata);            
    
   

	// ...
   
   
   
	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    
    
}



//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch (event.keysym.sym) {


    case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
    case SDLK_a:
        subtask = 1;
        break;
    case SDLK_b: 
        subtask = 2;
        
        break;
    case SDLK_c:
        subtask = 3;
       
        break;

    case SDLK_d:
        subtask = 4;
        break;
    case SDLK_e:
        subtask = 5;
        break;
    case SDLK_f:
        subtask = 6;
        break;

    case SDLK_1:
        if (!formulas) {
            formulas = true;
            filters = false;
            transformation = false;
            mesh = false;
            subtask = 1;
        }
        else {
            formulas = false;
        }
       
        break;

    case SDLK_2: //  increase current property
        if (!filters) {
            formulas = false;
            filters = true;
            transformation = false;
            mesh = false;
            subtask = 1;
        }
        else {
            filters = false;
        }

        
        break;
    case SDLK_3: // , decrease current property
        if (!transformation) {
            formulas = false;
            filters = false;
            transformation = true;
            mesh = false;
            subtask = 1;
        }
        else {
            transformation = false;
        }
        
        break;

    case SDLK_4:
        if (!mesh) {
            formulas = false;
            filters = false;
            transformation = false;
            mesh = true;
            subtask = 1;
        }
        else {
            mesh = false;
        }
        break;
    case SDLK_z:
        
       
        break;
    
    
    case SDLK_t:
        
      
        break;
    
    }


   
	
		
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
	
	/*if (event.button == SDL_BUTTON_LEFT) {
        start_x = mouse_position.x;
        start_y = mouse_position.y;
		
	}*/
}


void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
        //camera1.Move(Vector3(mouse_position.x - start_x, mouse_position.y - start_y, 0));
	
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
    if (event.button == SDL_BUTTON_LEFT) {
       camera1.Orbit(-mouse_delta.x * 0.03, Vector3::UP);
       camera1.Orbit(-mouse_delta.y *0.03,Vector3::RIGHT);
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
    float dy = event.preciseY * 0.03;
    camera1.Zoom(dy < 0 ? 1.1 : 0.9);
    int i;
}
void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}


