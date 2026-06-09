#pragma once

#include <raylib.h>
#include <cmath>
#include <string>
#include "shape.h"
#include "mm/vec2.h"


class Circle : public Shape{
public:
    float radius;           /*Circle Radius*/

    Circle(const std::string& name,float x,float y,float r, float speedX,float speedY,float* color);
    void Move(int width,int height) override;
    void Draw(const Font& font, int fontSize, const Color& fontColor, bool drawText) override;
};
