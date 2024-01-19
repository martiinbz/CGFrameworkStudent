#pragma once




#include "Image.h"  
#include "framework.h"

class Button
{
private:
    Image image;
    Vector2 position;

public:
    Button(const Image& img, const Vector2& pos);
    bool IsMouseInside(const Vector2& mousePosition);
    Image Button::GetImage();
    int Button::GetX();
    int Button::GetY();
 
};


