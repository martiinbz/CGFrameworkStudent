/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "button.h"
#include "image.h"



class Application
{

private:
	//ESTRUCTURAS DE LOS DIFERENTES VECTORES USADOS PARA ALMACENAR FORMAS
	struct Line
	{
		int start_x;
		int start_y;
		int end_x;
		int end_y;
		Color color;
	};
	struct Rectangle
	{
		int start_x;
		int start_y;
		int width;
		int height;
		Color color;
		bool fill;
		int border_width;
	};
	struct Circle
	{
		int start_x;
		int start_y;
		int radius;
		Color color;
		bool fill;
	};
	struct Triangle {
		Vector2 v1;
		Vector2 v2;
		Vector2 v3;
		Color color;
		bool fill;
	};
	struct Pixel {
		int x;
		int y;
		Color color;
	};
	struct Loaded_image {
		int x;
		int y;
	};
	

	struct Particle {
		Vector2 position;
		Vector2 velocity;
		Color color;
		float acceleration;
		float ttl;
		bool inactive;
	};

	//DECLARAMOS TODAS LAS VARIABLES QUE USAREMOS
	static const int MAX_PARTICLES = 100;
	Particle particles[MAX_PARTICLES];
	bool first_click, draw_lines, draw_rectangles, draw_circles, draw_triangles, paint_mode, animation, fill_shapes, increase_border_width, decrease_border_width, load_button, eraser_mode;
	int start_x, start_y;
	int end_x, end_y;
	int height, width;
	int draw_width, clicks;
	Vector2 v1, v2, v3;
	Color current_color;
	Image load, save, paint, black, red, green, blue, yellow, pink, cyan, white, eraser, line, rectangle, circle, triangle, fruits, increase, decrease, fill;
	Button loadbutton, savebutton, paintbutton, blackbutton, redbutton, greenbutton, bluebutton, yellowbutton, pinkbutton, cyanbutton, whitebutton, eraserbutton, linebutton, rectanglebutton, circlebutton, trianglebutton, increasebutton, decreasebutton, fillbutton;
	std::vector<Line> lines;
	std::vector<Rectangle> rectangles;
	std::vector<Circle> circles;
	std::vector<Triangle> triangles;
	std::vector<Pixel> pixels;
	std::vector<Loaded_image> loaded_images;
	
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
