#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "button.h";


Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);
	start_x = NULL;
	start_y = NULL;
	end_x = NULL;
	end_y = NULL;
	first_click = false;

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
	int x = 500;
	int y = 400;
	int w = 300;
	int h = 100;
	int r = 100;
	Vector2 p0(100.0f,200.0f);
	Vector2 p1(100.0f, 500.0f);
	Vector2 p2(500.0f, 200.0f);
	Image toolbar;
	toolbar.LoadPNG("images/toolbar.png", true);


	//CARGAMOS TODAS LAS IMAGENES
	Image load, save, black, red, green, blue, yellow, pink, cyan, white, eraser, line, rectangle, circle;

	load.LoadPNG("images/load.png", false);
	save.LoadPNG("images/save.png", false);
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



	Button loadbutton(load, Vector2(0, 10));
	Button savebutton(save, Vector2(40, 10));
	Button blackbutton(black, Vector2(80, 10));
	Button redbutton(red, Vector2(120, 10));
	Button greenbutton(green, Vector2(160, 10));
	Button bluebutton(blue, Vector2(200, 10));
	//Button yellowbutton(yellow, Vector2(240, 10));
	Button pinkbutton(pink, Vector2(280, 10));
	Button cyanbutton(cyan, Vector2(320, 10));
	//Button whitebutton(white, Vector2(360, 10));
	Button eraserbutton(eraser, Vector2(400, 10));
	Button linebutton(line, Vector2(440, 10));
	Button rectanglebutton(rectangle, Vector2(480, 10));
	Button circlebutton(circle, Vector2(520, 10));




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
	//framebuffer.DrawRect(x, y, w, h, Color(255, 0, 0), 5, TRUE, Color(0, 0, 0));
	framebuffer.DrawLineDDA(x, y, x + 100 * cos(time), y + 100 * sin(time), Color(0, 0, 0));
	//framebuffer.DrawCircle(x, y, r, Color(255, 0, 0), 1000, TRUE, Color(0, 0, 0));
	//framebuffer.DrawTriangle(p0, p1, p2, Color(255, 0, 0), TRUE, Color(0, 0, 0));


	for (const auto& line : lines)
	{
		framebuffer.DrawLineDDA(line.start_x, line.start_y, line.end_x, line.end_y, line.color);
	}
	if (first_click)
	{
		framebuffer.DrawLineDDA(start_x, start_y, mouse_position.x, mouse_position.y, Color(0, 0, 0));
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
		/*case SDLK_1: //DRAW LINE
		case SDLK_2: //DRAW RECTANGLE
		case SDLK_3: //DRAW CIRCLE
		case SDLK_4: //DRAW TRIANGLE
		case SDLK_5: //PAINT
		case SDLK_6: //ANIMATION
		case SDLK_f: //FILL SHAPES
		case SDLK_PLUS: //INCREASE BORDER WIDTH
		case SDLK_MINUS: //DECREASE BORDE WIDTH*/
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{

	if (event.button == SDL_BUTTON_LEFT) {
		start_x = mouse_position.x;
		start_y = mouse_position.y;
		first_click = true;
		std::cerr << "Start position: " << start_x << ", " << start_y << std::endl;
		 
		
		

		
	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

		if (first_click) {
			end_x = mouse_position.x;
			end_y = mouse_position.y;
			std::cerr << "Start position: " << start_x << ", " << start_y << std::endl;
			std::cerr << "End position: " << end_x << ", " << end_y << std::endl;
			lines.push_back({ start_x, start_y, end_x, end_y, Color(0, 0, 0) });
			


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
			framebuffer.DrawLineDDA(start_x, start_y, event.x,event.y, Color(0, 0, 0));


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