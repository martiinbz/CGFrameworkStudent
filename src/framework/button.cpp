/*class Button
{
private:
    Image image;
    Vector2 position;

public:
    Button(const Image& img, const Vector2& pos)
        : image(img), position(pos) {}

    bool IsMouseInside(const Vector2& mousePosition)
    {
        return mousePosition.x >= position.x && mousePosition.x < position.x + image.GetWidth() &&
            mousePosition.y >= position.y && mousePosition.y < position.y + image.GetHeight();
    }

    void Render(Image& framebuffer)
    {
        framebuffer.DrawImage(image, static_cast<int>(position.x), static_cast<int>(position.y), false);
    }
    // Load images for buttons
    Image lineButtonImage, rectangleButtonImage, circleButtonImage, triangleButtonImage, colorButtonImage,
        fillButtonImage, saveButtonImage, loadButtonImage, clearButtonImage, eraserButtonImage;

    lineButtonImage.LoadPNG("res/images/line_button.png", true);
    // Load other button images similarly...

    // Create buttons
    Button lineButton(lineButtonImage, Vector2(10, 10));
    // Create other buttons similarly...

    // Render buttons in your application loop
    
}; */
