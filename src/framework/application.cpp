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
    draw_entity = false;
    animation = false; 
    ortographic = false;
    perspective = false;
    change_near = false;
    change_far = false;
    change_fov = false;
    increase = false;
    decrease = false;
    texture_bool = false;
    interpolated_bool = false;
    oclussion = false;
    Vector3 t1 = Vector3(0, 0, 2);
    
    
    camera1.LookAt(Vector3(0.5,0,0),Vector3(0,0,0),Vector3::UP);
    
   
  
	
}

Application::~Application()
{
	
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
    
    quad.CreateQuad();
   //Shader* shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
    shader1 = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
  // shader1 = shader;
    
    
}


void Application::Render(void)
{
    
    
    shader1->Enable();
    //glEnable(GL_DEPTH_TEST);
    shader1->SetFloat("subtask", subtask);
    shader1->SetFloat("time", 1.0);
    quad.Render();
    //glDisable(GL_DEPTH_TEST);
   
    shader1->Disable();

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

    case SDLK_k:
       
        break;

    case SDLK_PLUS: //  increase current property
        
        break;
    case SDLK_MINUS: // , decrease current property
        
        break;



    case SDLK_h:
       
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


