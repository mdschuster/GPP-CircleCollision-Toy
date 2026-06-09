#include "circle.h"
#include <string>
#include <cmath>
#include <algorithm>

/**
 * Creates a Circle object
 * @param name    Name/ID of object
 * @param x       X position
 * @param y       Y position
 * @param r       radius
 * @param speedX  X speed
 * @param speedY  Y speed
 * @param color   Fill color
 */
Circle::Circle(const std::string &name, float x, float y, float r, float speedX, float speedY, float *color)
        : Shape(name, x, y, speedX, speedY, color), radius(r) {}

/**
 * Moves and rotates object, including bouncing off of screen edges
 * @param width  Screen width
 * @param height Screen Height
 */
void Circle::Move(int width, int height) {
    x += speedX;
    y += speedY;
    //update vertices
    float scaledR=scaleFactor*radius;

    if (x < 0+scaledR || x + scaledR > width) {
        speedX *= -1;
        x = std::clamp(x, scaledR, width - scaledR);
    }
    if (y < 0+scaledR || y + scaledR > height) {
        speedY *= -1;
        y = std::clamp(y, scaledR , height - scaledR);
    }
}

/**
 * Draws filled version of the object with Name/ID in the center and vertices as circles. If it is currently
 * colliding with another object, the outline will be drawn in a different color.
 * @param font      Font name
 * @param fontSize  Font size
 * @param fontColor Font color
 * @param drawText  Flag to draw text
 */
void Circle::Draw(const Font &font, int fontSize, const Color &fontColor, bool drawText) {
    float scaledR=scaleFactor*radius;
    //Draw Filled Circle
    DrawCircle(x,y,scaledR,ColorFromNormalized({color[0], color[1], color[2], 1.0f}));

    //Draw Circle Lines
    Color c = ColorFromNormalized({lineColor[0], lineColor[1], lineColor[2], 1.0f});
    //can't use dra circle lines because it can't do line thickness
    //So, will draw a many sided polygon
    DrawPolyLinesEx({x,y}, 60, scaledR, 0.0f, 4, c);

    //Draw Text
    if (drawText) {
        Vector2 textSize = MeasureTextEx(font, name.c_str(), fontSize, 1);
        DrawTextEx(font, name.c_str(), {x - textSize.x / 2, y - textSize.y / 2}, fontSize, 1, fontColor);
    }
}
