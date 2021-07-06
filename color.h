#ifndef COLOR_H_
#define COLOR_H_

#include <cinttypes>

class Color
{

    static const Color Empty;

public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(Color &color);

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(Color &color);
};

#endif