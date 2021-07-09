#include "color.h"

#include <iostream>
#include <cstdlib>

const Color Color::Empty = Color(0x7f7f7f);
const Color Color::Cyan = Color(0x00ffff);
const Color Color::Yellow = Color(0xffff00);
const Color Color::Purple = Color(0x800080);
const Color Color::Green = Color(0x00ff00);
const Color Color::Red = Color(0xff0000);
const Color Color::Blue = Color(0x0000ff);
const Color Color::Orange = Color(0xff7f00);
const Color Color::Grey = Color(0x7f7f7f);

Color::Color(uint32_t color)
{
    this->r = (color & 0xFF0000) >> 16;
    this->g = (color & 0xFF00) >> 8;
    this->b = (color & 0xFF);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r),
                                                g(g), b(b)
{
}

Color::Color(const Color &color) : Color(color.r, color.g, color.b)
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
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}