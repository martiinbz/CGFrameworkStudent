/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "button.h"
#include "image.h"
#include "entity.h"



class Application
{

private:
	int w, h;
	int start_x, start_y, start_z, end_x, end_y, end_z, current_fov, current_near, current_far;
	Mesh mesh; 
	Mesh mesh2, mesh3;
	Matrix44 modelMatrix, modelMatrix2, modelMatrix3, rotationmatrix, translationmatrix, rotationmatrix2, translationmatrix2, rotationmatrix3, translationmatrix3, rotationmatrix4, translationmatrix4;
	Entity entity;
	Entity entity2, entity3, entity4;
	Camera camera1;
	bool draw_entity, animation, ortographic, perspective, change_near, change_far, change_fov, increase, decrease, interpolated_bool, texture_bool, oclussion;
	Image texture1;

	
	
public:

	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;
	FloatImage zbuffer;
	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}

};
