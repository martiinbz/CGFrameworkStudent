#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "image.h"
#include "button.h"



Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);
	start_x = NULL;
	start_y = NULL;
	end_x = NULL;
	end_y = NULL;
	height = NULL;
	width = NULL;
	first_click = false;
	draw_lines = false;
	draw_triangles = false;
	draw_rectangles = false;
	draw_circles = false;
	paint_mode = false;
	

	

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);	
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
	Vector2 v1, v2, v3;

	//CARGAMOS TODAS LAS IMAGENES
	

	
	load.LoadPNG("images/load.png", false);
	save.LoadPNG("images/save.png", false);
	paint.LoadPNG("images/pincel.png", false);
	black.LoadPNG("images/black.png", false);
	red.LoadPNG("images/red.png", false);
	green.LoadPNG("images/green.png", false);
	blue.LoadPNG("images/blue.png", false);
	//yellow.LoadPNG("images/yellow.png", false);
	pink.LoadPNG("images/pink.png", false);
	cyan.LoadPNG("images/cyan.png", false);
	//white.LoadPNG("images/white.png", false);
	eraser.LoadPNG("images/eraser.png", false);
	line.LoadPNG("images/line.png", false);
	rectangle.LoadPNG("images/rectangle.png", false);
	circle.LoadPNG("images/circle.png", false);


	//CREAMOS BOTONES PARA TODAS LAS IMAGENES
	
	loadbutton = std::move(Button(load, Vector2(0,10)));
	savebutton = std::move(Button(save, Vector2(40, 10)));
	blackbutton = std::move(Button(black, Vector2(80, 10)));
	redbutton = std::move(Button(red, Vector2(120, 10)));
	greenbutton = std::move(Button(green, Vector2(160, 10)));
	bluebutton = std::move(Button(blue, Vector2(200, 10)));
	yellowbutton = std::move(Button(yellow, Vector2(240, 10)));
	pinkbutton = std::move(Button(pink, Vector2(280, 10)));
	cyanbutton = std::move(Button(cyan, Vector2(320, 10)));
	whitebutton = std::move(Button(white, Vector2(360, 10)));
	eraserbutton = std::move(Button(eraser, Vector2(400, 10)));
	linebutton = std::move(Button(line, Vector2(440, 10)));
	rectanglebutton = std::move(Button(rectangle, Vector2(480, 10)));
	circlebutton = std::move(Button(circle, Vector2(520, 10)));
	paintbutton = std::move(Button(paint, Vector2(560, 10)));
	


	




	framebuffer.Fill(Color::WHITE);
	framebuffer.DrawImage(loadbutton.GetImage(), loadbutton.GetX(), loadbutton.GetY(), 5);
	framebuffer.DrawImage(savebutton.GetImage(), savebutton.GetX(), savebutton.GetY(), 5);
	framebuffer.DrawImage(blackbutton.GetImage(), blackbutton.GetX(), blackbutton.GetY(), 5);
	framebuffer.DrawImage(redbutton.GetImage(), redbutton.GetX(), redbutton.GetY(), 5);
	framebuffer.DrawImage(greenbutton.GetImage(), greenbutton.GetX(), greenbutton.GetY(), 5);
	framebuffer.DrawImage(bluebutton.GetImage(), bluebutton.GetX(), bluebutton.GetY(), 5);
	//framebuffer.DrawImage(yellowbutton.GetImage(), yellowbutton.GetX(), yellowbutton.GetY(), 5);
	framebuffer.DrawImage(pinkbutton.GetImage(), pinkbutton.GetX(), pinkbutton.GetY(), 5);
	framebuffer.DrawImage(cyanbutton.GetImage(), cyanbutton.GetX(), cyanbutton.GetY(), 5);
	//framebuffer.DrawImage(whitebutton.GetImage(), whitebutton.GetX(), whitebutton.GetY(), 5);
	framebuffer.DrawImage(eraserbutton.GetImage(), eraserbutton.GetX(), eraserbutton.GetY(), 5);
	framebuffer.DrawImage(linebutton.GetImage(), linebutton.GetX(), linebutton.GetY(), 5);
	framebuffer.DrawImage(rectanglebutton.GetImage(), rectanglebutton.GetX(), rectanglebutton.GetY(), 5);
	framebuffer.DrawImage(circlebutton.GetImage(), circlebutton.GetX(), circlebutton.GetY(), 5);
	framebuffer.DrawImage(paintbutton.GetImage(), paintbutton.GetX(), paintbutton.GetY(), 5);
	//fill button
	//increase width
	//decrease width
	
	

	
	
	for (const auto& line : lines)
	{
		framebuffer.DrawLineDDA(line.start_x, line.start_y, line.end_x, line.end_y, line.color);
	}
	if ( draw_lines && first_click)
	{
		framebuffer.DrawLineDDA(start_x, start_y, mouse_position.x, mouse_position.y, Color(0, 0, 0));
	}
	for (const auto& rect : rectangles)
	{
		framebuffer.DrawRect(rect.start_x, rect.start_y, rect.width, rect.height, Color(0,0,0),5,true,Color(0,255,0));
	}
	/*if (draw_rectangles && first_click)
	{
		framebuffer.DrawRect(start_x, start_y, mouse_position.x, mouse_position.y, Color(0, 0, 0));
	}*/
	for (const auto& circ : circles)
	{
		framebuffer.DrawCircle(circ.start_x, circ.start_y, circ.radius, Color(0, 0, 0), 5, true, Color(0, 255, 0));
	}
	for (const auto& trian : triangles)
	{
		framebuffer.DrawTriangle(trian.v1, trian.v2, trian.v3, Color(0, 0, 0),false,Color(0,255,0));
	}
	for (const auto& pix : pixels)
	{
		framebuffer.SetPixel(pix.x, pix.y,Color(0, 0, 0));
	}






	
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
		case SDLK_1://DRAW LINE
		{
			if (!draw_lines) {
				draw_lines = true;

				draw_triangles = false;
				draw_rectangles = false;
				draw_circles = false;
				paint_mode = false;


			}
			else {
				draw_lines = false;
			}
			break;
		}
		case SDLK_2: //DRAW RECTANGLE
		{
			if (!draw_rectangles) {
				draw_rectangles = true;

				draw_lines = false;
				draw_triangles = false;
				draw_circles = false;
				paint_mode = false;
			}
			else {
				draw_rectangles = false;
			}
			break;
			
		}
	
		case SDLK_3: //DRAW CIRCLE
		{
			if (!draw_circles) {
				draw_circles = true;

				draw_rectangles = false;
				draw_lines = false;
				draw_triangles = false;
				paint_mode = false;
			}
			else {
				draw_circles = false;
			}
			break;
		}
		
		
		case SDLK_4: //DRAW TRIANGLE
		{
			if (!draw_triangles) {
				draw_triangles = true;

				draw_circles = false;
				draw_rectangles = false;
				draw_lines = false;
				paint_mode = false;

			}
			else {
				draw_triangles = false;
			}	
			break;
		
			
		}
			
		case SDLK_5: //PAINT
		{
			if (!paint_mode) {
				paint_mode = true;

				draw_triangles = false;
				draw_circles = false;
				draw_rectangles = false;
				draw_lines = false;
				

			}
			else {
				paint_mode = false;

			}	
			break;	
		}
		case SDLK_6: //ANIMATION
		{
			if (!animation) {
				animation = true;
			}
			
		}
			
		case SDLK_f: //FILL SHAPES
		{
			if (!fill_shapes) {
				fill_shapes = true;
			}
			
		}
		case SDLK_PLUS: //INCREASE BORDER WIDTH
		{
			if (!increase_border_width) {
				increase_border_width = true;
			}
			else {
				increase_border_width = false;
			}
		}
		/*case SDLK_MINUS: //DECREASE BORDER WIDTH
			if(!decrease_borde_width){
				decrease_borde_width=true;
			}
			else{
				decrease_borde_width=false;
			} */
			
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	
	if (event.button == SDL_BUTTON_LEFT) {
		if (draw_lines || linebutton.IsMouseInside(mouse_position)) {
			start_x = mouse_position.x;
			start_y = mouse_position.y;
			first_click = true;
			draw_lines = true;
		}
		if (draw_rectangles) {
			start_x = mouse_position.x;
			start_y = mouse_position.y;
			first_click = true;
		}
		if (draw_circles) {
			start_x = mouse_position.x;
			start_y = mouse_position.y;
			first_click = true;
		}
		if (draw_triangles){
			v1=Vector2(mouse_position.x, mouse_position.y);
			first_click = true;
		}
		if (paint_mode) {
			first_click = true;
		}
	
	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

		if (draw_lines) {
			if (first_click) {
				end_x = mouse_position.x;
				end_y = mouse_position.y;
				

				lines.push_back({ start_x, start_y, end_x, end_y, Color(0, 0, 0) });



			}
		}
		if (draw_rectangles) {
			if (first_click) {

				width = mouse_position.x - start_x;
				height = mouse_position.y - start_y;

				
				rectangles.push_back({ start_x, start_y, width, height, Color(0, 0, 0) });


			}
		}
		if (draw_circles) {
			if (first_click) {

				int radius = mouse_position.x - start_x;


				circles.push_back({ start_x, start_y,radius, Color(0, 0, 0) });


			}


		}
		if (draw_triangles){
			if(first_click){
				v2= Vector2(mouse_position.x, mouse_position.y);
				v3= Vector2(v2.x + (v2.x - v1.x), v1.y);

				triangles.push_back({ v1,v2,v3, Color(0, 0, 0) });
				
			}
		}
		



		first_click = false;
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {

		if (first_click) {
			mouse_position.x = event.x;
			mouse_position.y = event.y;
		}
		if (paint_mode && first_click) {
			pixels.push_back({ event.x,event.y,Color(0,0,0)});
		}

	
		
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

