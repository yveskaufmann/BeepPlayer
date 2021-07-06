#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r),
                                                g(g), b(b)
{
}

Color::Color(Color &color) : Color(color.r, color.g, color.b)
{
}

void Color::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setColor(Color &color)
{
    this->setColor(color.r,
                   color.g,
                   color.b);
}