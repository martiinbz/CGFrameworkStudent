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

    // Initialize your entities and camera here
    // Example: 
	// En tu aplicación donde creas una instancia de Entity
	 // Crear una instancia de Entity con la matriz modelo inicial
   
	
	
}

Application::~Application()
{
	
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;

}

// Render one frame
void Application::Render(void)
{
	// ...
    Entity entity;
    
    framebuffer.Fill(Color::BLACK);
    camera.UpdateViewMatrix();

    // Update the projection matrix
    camera.UpdateProjectionMatrix();

    // Render the entity using the updated matrices
    entity1.Render(&framebuffer, &camera, Color(255, 255, 255));
    framebuffer.Render();
		
	
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
	/*case SDLK_1: // "1" key, draw single entity
        // Set up or switch to drawing a single entity
        break;
    case SDLK_2: // "2" key, draw multiple animated entities
        // Set up or switch to drawing multiple animated entities
        break;
    case SDLK_O: // "O" key, set orthographic camera mode
        // Set camera to orthographic mode
        break;
    case SDLK_P: // "P" key, set perspective camera mode
        // Set camera to perspective mode
        break;
    case SDLK_N: // "N" key, set current property to CAMERA NEAR
        // Set the current property to camera near
        break;
    case SDLK_F: // "F" key, set current property to CAMERA FAR
        // Set the current property to camera far
        break;
    case SDLK_PLUS: // "+" key, increase current property
        // Increase the current property
        break;
    case SDLK_MINUS: // "-" key, decrease current property
        // Decrease the current property
        break;
    }*/


	}
		
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{
	
	if (event.button == SDL_BUTTON_LEFT) {
		
	}
}


void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
	
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	// Handle mouse motion event
    // Use event.x and event.y for mouse coordinates

    // Additional mouse move events if needed
	if (event.button == SDL_BUTTON_LEFT) {
		

	
		
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}


