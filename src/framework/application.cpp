#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "image.h"
#include "button.h"
#include "ParticleSystem.h"



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
	draw_width = 2;
	current_color = Color::WHITE;
	fill_shapes = false;
	load_button = false;
	eraser_mode = false;
	animation = false;

	

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);	
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		particles[i].position.x = static_cast<float>(rand() % 1280);
		particles[i].position.y = static_cast<float>(rand() % 700);
		particles[i].velocity.x = static_cast<float>(rand() % 1000) / 100.0f - 0.5f;  // Random normalized velocity
		particles[i].velocity.y = static_cast<float>(rand() % 1000) / 100.0f - 0.5f;
		particles[i].color = Color::YELLOW;  // White color
		particles[i].acceleration = 0.1f;
		particles[i].ttl = static_cast<float>(rand() % 100) / 50.0f;  // Random time to live
		particles[i].inactive = false;
	}
	
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
	yellow.LoadPNG("images/yellow.png", false);
	pink.LoadPNG("images/pink.png", false);
	cyan.LoadPNG("images/cyan.png", false);
	white.LoadPNG("images/white.png", false);
	eraser.LoadPNG("images/eraser.png", false);
	line.LoadPNG("images/line.png", false);
	rectangle.LoadPNG("images/rectangle.png", false);
	circle.LoadPNG("images/circle.png", false);
	triangle.LoadPNG("images/triangle.png", true);
	fruits.LoadPNG("images/eraser.png", false); //CAMBIARLA
	increase.LoadPNG("images/increase.png", false);
	decrease.LoadPNG("images/decrease.png", false);
	fill.LoadPNG("images/fill.png", true);

	

	//INICIALIZAMOS TODOS LOS BOTONES
	
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
	trianglebutton = std::move(Button(triangle, Vector2(600, 10)));
	increasebutton = std::move(Button(increase, Vector2(640, 10)));
	decreasebutton = std::move(Button(decrease, Vector2(680, 10)));
	fillbutton = std::move(Button(fill, Vector2(720, 10)));


	


	



	//DIBUJAMOS TODAS LAS IMAGENES EN EL FRAMEBUFFER
	framebuffer.Fill(Color::BLACK);
	framebuffer.DrawRect(0, 0, 1280, 50, Color::GRAY, 5, true, Color::GRAY);
	framebuffer.DrawImage(loadbutton.GetImage(), loadbutton.GetX(), loadbutton.GetY(), 5);
	framebuffer.DrawImage(savebutton.GetImage(), savebutton.GetX(), savebutton.GetY(), 5);
	framebuffer.DrawImage(blackbutton.GetImage(), blackbutton.GetX(), blackbutton.GetY(), 5);
	framebuffer.DrawImage(redbutton.GetImage(), redbutton.GetX(), redbutton.GetY(), 5);
	framebuffer.DrawImage(greenbutton.GetImage(), greenbutton.GetX(), greenbutton.GetY(), 5);
	framebuffer.DrawImage(bluebutton.GetImage(), bluebutton.GetX(), bluebutton.GetY(), 5);
	framebuffer.DrawImage(yellowbutton.GetImage(), yellowbutton.GetX(), yellowbutton.GetY(), 5);
	framebuffer.DrawImage(pinkbutton.GetImage(), pinkbutton.GetX(), pinkbutton.GetY(), 5);
	framebuffer.DrawImage(cyanbutton.GetImage(), cyanbutton.GetX(), cyanbutton.GetY(), 5);
	framebuffer.DrawImage(whitebutton.GetImage(), whitebutton.GetX(), whitebutton.GetY(), 5);
	framebuffer.DrawImage(eraserbutton.GetImage(), eraserbutton.GetX(), eraserbutton.GetY(), 5);
	framebuffer.DrawImage(linebutton.GetImage(), linebutton.GetX(), linebutton.GetY(), 5);
	framebuffer.DrawImage(rectanglebutton.GetImage(), rectanglebutton.GetX(), rectanglebutton.GetY(), 5);
	framebuffer.DrawImage(circlebutton.GetImage(), circlebutton.GetX(), circlebutton.GetY(), 5);
	framebuffer.DrawImage(paintbutton.GetImage(), paintbutton.GetX(), paintbutton.GetY(), 5);
	framebuffer.DrawImage(trianglebutton.GetImage(), trianglebutton.GetX(), trianglebutton.GetY(), 5);
	framebuffer.DrawImage(increasebutton.GetImage(), increasebutton.GetX(), increasebutton.GetY(), 5);
	framebuffer.DrawImage(decreasebutton.GetImage(), decreasebutton.GetX(), decreasebutton.GetY(), 5);
	framebuffer.DrawImage(fillbutton.GetImage(), fillbutton.GetX(), fillbutton.GetY(), 5);
	
	
	

	
	//ESTOS BUCLES SIRVEN PARA QUE LAS FORMAS SE QUEDEN EN PANTALLA (si no, al dibujar otra se borraria la anterior)
	//los ifs sirven para ir viendo la figura a medida que la dibujas (mientras tienes el mouse apretado) (solo con lineas y circulos)
	for (const auto& line : lines)
	{
		framebuffer.DrawLineDDA(line.start_x, line.start_y, line.end_x, line.end_y, line.color);
	}
	if ( draw_lines && first_click)
	{
		framebuffer.DrawLineDDA(start_x, start_y, mouse_position.x, mouse_position.y, current_color);
	}
	for (const auto& rect : rectangles)
	{
		framebuffer.DrawRect(rect.start_x, rect.start_y, rect.width, rect.height, rect.color,rect.border_width,rect.fill,rect.color);
	}
	
	for (const auto& circ : circles)
	{
		framebuffer.DrawCircle(circ.start_x, circ.start_y, circ.radius, circ.color, draw_width, circ.fill, circ.color);
	}
	if (draw_circles && first_click)
	{
		framebuffer.DrawCircle(start_x, start_y, mouse_position.x-start_x, current_color,draw_width,fill_shapes,current_color);
	}
	for (const auto& trian : triangles)
	{
		framebuffer.DrawTriangle(trian.v1, trian.v2, trian.v3, trian.color,trian.fill,trian.color);
	}
	for (const auto& pix : pixels)
	{
		framebuffer.SetPixel(pix.x, pix.y,pix.color);
	}
	for (const auto& img : loaded_images)
	{
		framebuffer.DrawImage(fruits,img.x, img.y,fruits.height);
	}
	
	if (animation) {
		for (int i = 0; i < MAX_PARTICLES; ++i) {

			framebuffer.SetPixel(static_cast<int>(particles[i].position.x), static_cast<int>(particles[i].position.y), particles[i].color);

		}
	}
	



	framebuffer.Render();
	
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	if (animation) {

		for (int i = 0; i < MAX_PARTICLES; ++i) {
			if (!particles[i].inactive) {
				particles[i].position.x += particles[i].velocity.x * seconds_elapsed;
				particles[i].position.y += particles[i].velocity.y * seconds_elapsed;

				// Update velocity or acceleration as needed
				//particles[i].velocity.x += particles[i].acceleration * seconds_elapsed;

				particles[i].ttl -= seconds_elapsed;

				if (particles[i].position.x == 1279 || particles[i].position.x == 1 || particles[i].position.y == 699 || particles[i].position.y == 1) {
					particles[i].inactive = true;
				}
			}
		}


	}
	
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
				eraser_mode = false;
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
				eraser_mode = false;
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
				eraser_mode = false;
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
				eraser_mode = false;
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
				eraser_mode = false;
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
			else {
				animation = false;
			}
		}
			
		case SDLK_f: //FILL SHAPES
		{
			if (!fill_shapes) {
				fill_shapes = true;
			}
			else {
				fill_shapes = false;
			}
			
		}
		case SDLK_PLUS: //INCREASE BORDER WIDTH
		{
			draw_width += 1;
		}
		case SDLK_MINUS: //DECREASE BORDER WIDTH
		{
			draw_width -= 1;
		}
			
			
	}
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{

	if (event.button == SDL_BUTTON_LEFT) {
		//LÓGICA PARA CUANDO SE APRIETA UN BOTÓN
		if (linebutton.IsMouseInside(mouse_position))
		{
			if (!draw_lines) {
				draw_lines = true;

				draw_triangles = false;
				draw_rectangles = false;
				draw_circles = false;
				paint_mode = false;
				eraser_mode = false;

			}
			else {
				draw_lines = false;

			}

		}
		if (rectanglebutton.IsMouseInside(mouse_position)) {
			if (!draw_rectangles) {
				draw_rectangles = true;

				draw_lines = false;
				draw_triangles = false;
				draw_circles = false;
				paint_mode = false;
				eraser_mode = false;
			}
			else {
				draw_rectangles = false;
			}

		}
		if (circlebutton.IsMouseInside(mouse_position)) {
			if (!draw_circles) {
				draw_rectangles = false;
				draw_lines = false;
				draw_triangles = false;
				draw_circles = true;
				paint_mode = false;
				eraser_mode = false;
			}
			else {
				draw_circles = false;
			}

		}
		if (trianglebutton.IsMouseInside(mouse_position)) {
			if (!draw_triangles) {
				draw_triangles = true;

				draw_lines = false;
				draw_rectangles = false;
				draw_circles = false;
				paint_mode = false;
				eraser_mode = false;
			}
			else {
				draw_triangles = false;
			}

		}
		if (paintbutton.IsMouseInside(mouse_position)) {
			if (!paint_mode) {
				draw_rectangles = false;
				draw_lines = false;
				draw_triangles = false;
				draw_circles = false;
				paint_mode = true;
				eraser_mode = false;
			}
			else {
				paint_mode = false;
			}

		}
		if (loadbutton.IsMouseInside(mouse_position)) {
			if (!load_button) {
				load_button = true;

				draw_rectangles = false;
				draw_lines = false;
				draw_triangles = false;
				draw_circles = false;
				paint_mode = false;
				eraser_mode = false;
			}
			else {
				load_button = false;
			}

		}
		if (blackbutton.IsMouseInside(mouse_position)) {
			current_color = Color::BLACK;
		}
		if (bluebutton.IsMouseInside(mouse_position)) {
			current_color = Color::BLUE;
		}
		if (cyanbutton.IsMouseInside(mouse_position)) {
			current_color = Color::CYAN;
		}
		if (greenbutton.IsMouseInside(mouse_position)) {
			current_color = Color::GREEN;
		}
		if (pinkbutton.IsMouseInside(mouse_position)) {
			current_color = Color::PURPLE;
		}
		if (redbutton.IsMouseInside(mouse_position)) {
			current_color = Color::RED;
		}
		if (whitebutton.IsMouseInside(mouse_position)) {
			current_color = Color::WHITE;
		}
		if (yellowbutton.IsMouseInside(mouse_position)) {
			current_color = Color::YELLOW;
		}
		if (fillbutton.IsMouseInside(mouse_position)) {
			if (!fill_shapes) {
				fill_shapes = true;

			}
			else {
				fill_shapes = false;
			}

		}
		if (increasebutton.IsMouseInside(mouse_position)) {
			draw_width += 1;
		}
		if (decreasebutton.IsMouseInside(mouse_position)) {
			draw_width -= 1;
		}
		if (savebutton.IsMouseInside(mouse_position)) {
			framebuffer.SaveTGA("paint"); //this saves a tga in the res/textures folder.
		}
		if (eraserbutton.IsMouseInside(mouse_position)) {
			if (!eraser_mode) {
				eraser_mode = true;
				draw_rectangles = false;
				draw_lines = false;
				draw_triangles = false;
				draw_circles = false;
				paint_mode = false;
			}
			else {
				eraser_mode = false;
			}
		}
		//LÓGICA PARA CUANDO SE APRIETA LA PANTALLA
		if (draw_lines) {
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
		if (draw_triangles) {
			v1 = Vector2(mouse_position.x, mouse_position.y);
			first_click = true;
		}
		if (paint_mode) {
			first_click = true;
		}
		if (load_button) {
			start_x = mouse_position.x;
			start_y = mouse_position.y;
			loaded_images.push_back({ start_x,start_y });
		}
		if (eraser_mode) {
			first_click = true;
		}

	}
}


void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		//LÓGICA PARA CUANDO SE SUELTA EL CLICK, DEPENDIENDO DE QUÉ MODO ESTÉ ACTIVADO
		if (draw_lines) {
			if (first_click) {
				end_x = mouse_position.x;
				end_y = mouse_position.y;
				lines.push_back({ start_x, start_y, end_x, end_y, current_color });
			}
		}
		if (draw_rectangles) {
			if (first_click) {

				width = mouse_position.x - start_x; //calculo de altura y anchura
				height = mouse_position.y - start_y;
				rectangles.push_back({ start_x, start_y, width, height, current_color,fill_shapes,draw_width });
			}
		}
		if (draw_circles) {
			if (first_click) {
				int radius = mouse_position.x - start_x;
				circles.push_back({ start_x, start_y,radius, current_color,fill_shapes });

			}


		}
		if (draw_triangles){
			if(first_click){
				v2= Vector2(mouse_position.x, mouse_position.y);
				v3= Vector2(v2.x + (v2.x - v1.x), v1.y); //hemos decidido hacer triangulos isosceles

				triangles.push_back({ v1,v2,v3, current_color,fill_shapes });
				
			}
		}
		first_click = false;
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		//LÓGICA MIENTRA SE MUEVE EL RATÓN CON EL CLICK APRETADO
		if (first_click) {
			mouse_position.x = event.x;
			mouse_position.y = event.y;
		}
		if (paint_mode && first_click) {
			pixels.push_back({ event.x,event.y,current_color }); //para ir pintando pixeles
		}
		if (eraser_mode && first_click) {
			pixels.push_back({ event.x,event.y,Color:: WHITE }); //painting the pixels white will work as an eraser
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

void Application::InitParticles(float seconds_elapsed) {
	

	for (int i = 0; i < MAX_PARTICLES; ++i) {
		particles[i].position.x = static_cast<float>(rand() % 800);  // Assuming a 800x600 framebuffer
		particles[i].position.y = static_cast<float>(rand() % 600);
		particles[i].velocity.x = static_cast<float>(rand() % 100) / 100.0f - 0.5f;  // Random normalized velocity
		particles[i].velocity.y = static_cast<float>(rand() % 100) / 100.0f - 0.5f;
		particles[i].color = Color::BLACK;  // White color
		particles[i].acceleration = 0.1f;
		particles[i].ttl = static_cast<float>(rand() % 100) / 50.0f;  // Random time to live
		particles[i].inactive = false;
	}
}
