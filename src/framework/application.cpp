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
    mesh.LoadOBJ("/meshes/lee.obj");
    mesh2.LoadOBJ("/meshes/anna.obj");
    mesh3.LoadOBJ("/meshes/cleo.obj");
    
    rotationmatrix.SetIdentity(); // (DEG2RAD * 45, { 0,1,0 });
    translationmatrix.SetTranslation(0,0,0.0);
    rotationmatrix2.SetRotation(DEG2RAD * 90, { 0,1,0 });
    translationmatrix2.SetTranslation(0.4, 0.3,0);
    rotationmatrix3.SetRotation(DEG2RAD * 90, { 0,1,0 });
    translationmatrix3.SetTranslation(0.2,-0.3, 0);
    
    texture1.LoadTGA("/textures/lee_color_specular.tga");

    entity = Entity(mesh, rotationmatrix,translationmatrix,texture1);
   /* entity2 = Entity(mesh2, rotationmatrix2, translationmatrix2);
    entity3 = Entity(mesh3, rotationmatrix3, translationmatrix3);
    entity4 = Entity(mesh3, rotationmatrix4, translationmatrix4);*/
    
   
   
    camera1.LookAt(Vector3(0.5,0,0),Vector3(0,0,0),Vector3::UP);
    
   
   
	
}

Application::~Application()
{
	
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
    shader.Get("/shaders/quad.vs", "/shaders/quad.fs");
 
    
    quad.CreateQuad();
    
}


void Application::Render(void)
{
    

	
    shader.Enable();

    glEnable(GL_DEPTH_TEST);
    shader.SetFloat("time", time);
    quad.Render();
    glDisable(GL_DEPTH_TEST);
    
   // shader.Disable();

	// ...
   
    framebuffer.Fill(Color::BLACK);
  
    
    //if (draw_entity) {
     entity.Render(&framebuffer, &camera1,&zbuffer,texture_bool,interpolated_bool,oclussion);
    
    if (animation) {
       /*entity.Render(&framebuffer, &camera1, &zbuffer);
        entity2.Render(&framebuffer, &camera1, &zbuffer);
        entity3.Render(&framebuffer, &camera1, &zbuffer);*/
    };
    if (ortographic) {
        camera1.SetOrthographic(0, 10, 0,10,0.01, 100);
    }
    if (perspective) {
        camera1.SetPerspective(DEG2RAD*current_fov, w/h, current_near,current_far);

    }
   
   // framebuffer.DrawTriangleInterpolated(Vector3(700, 200, 1), Vector3(300, 600, 1), Vector3(600, 500, 1), Color::RED, Color::GREEN, Color::BLUE);
    zbuffer.Fill(FLT_MAX);
    framebuffer.Render();

	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    if (animation) {
        entity.Update(seconds_elapsed);
        entity2.Update(seconds_elapsed / 2);
        entity3.Update(seconds_elapsed*2);
    };
    
}



//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch (event.keysym.sym) {


    case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
    case SDLK_1: // draw single entity
        if (!draw_entity) {
            draw_entity = true;
        }
        else {
            draw_entity = false;
        }
        break;
    case SDLK_2: //  draw multiple animated entities

        if (!animation) {
            animation = true;
        }
        else {
            animation = false;
        }
        break;
    case SDLK_o:
        // Set camera to orthographic mode
        if (!ortographic) {
            ortographic = true;
            perspective = false;
        }
        else {
            ortographic = false;
            perspective = false;
        }
        break;

    case SDLK_p:
        // Set camera to perspective mode
        if (!perspective) {
            perspective = true;
            ortographic = false;
        }
        else {
            perspective = false;

        }
        break;
    case SDLK_n:
        // Set the current property to camera near
        if (!change_near) {
            change_near = true;
            change_fov = false;
            change_far = false;
        }
        else {
            change_near = false;
        }
        break;
    case SDLK_v:
        // Set the current property to fov
        if (!change_fov) {
            change_fov = true;
            change_near = false;
            change_far = false;

        }
        else {
            change_fov = false;
        }
        break;

    case SDLK_f:
        // Set the current property to camera far
        if (!change_far) {
            change_far = true;
            change_near = false;
            change_fov = false;
        }
        else {
            change_far = false;
        }
        break;

    case SDLK_PLUS: //  increase current property
        if (change_fov) {
            current_fov += 90;
        }
        else if (change_near) {
            current_near += 0.03;

        }
        else if (change_far) {
            current_far += 20;
        }
        break;
    case SDLK_MINUS: // , decrease current property
        if (change_fov) {
            current_fov -= 90;
        }
        else if (change_near) {
            current_near -= 0.03;

        }
        else if (change_far) {
            current_far -= 200;
        }
        break;



    case SDLK_c:
        
        if (!interpolated_bool) {
            interpolated_bool = true;
            texture_bool = false;

        }
        else {
            interpolated_bool = false;
        }
        break;
    case SDLK_z:
        
        if (!oclussion) {
            oclussion = true;

        }
        else {
           oclussion = false;
        }
        break;
    
    
    case SDLK_t:
        
        if (!texture_bool) {
            interpolated_bool = false;
            texture_bool = true;

        }
        else {
            texture_bool = false;
        }
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


