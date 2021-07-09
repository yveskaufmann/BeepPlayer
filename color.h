#ifndef COLOR_H_
#define COLOR_H_

#include <cinttypes>

class Color
{

public:
    static const Color Empty;
    static const Color Cyan;
    static const Color Yellow;
    static const Color Purple;
    static const Color Green;
    static const Color Red;
    static const Color Blue;
    static const Color Orange;
    static const Color Grey;

    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(uint32_t color);
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(const Color &color);

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(Color &color);
};

#endif