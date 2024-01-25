
#include "image.h";
#include "framework.h";
#include "button.h";




Button::Button() {

}
Button::Button(const Image& img, const Vector2& pos) {
    image = img;
    position = pos;

    }
        

    bool Button::IsMouseInside(const Vector2& mousePosition)
    {
        return mousePosition.x >= position.x && mousePosition.x < position.x + image.width &&
            mousePosition.y >= position.y && mousePosition.y < position.y + image.height;
    }
    Image Button::GetImage() {
        return image;

    }
    int Button::GetX() {
        return position.x;
    }
    int Button::GetY() {
        return position.y;
    }
    
   

        



