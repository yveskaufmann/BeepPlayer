#include "field.h"
#include "color.h"

Field::Field() : free(true), color(Color::Empty)
{
}

void Field::unset()
{
    this->free = true;
    this->color = Color::Empty;
}

void Field::set(const Color &color)
{
    this->free = false;
    this->color = color;
}

void Field::setFrom(const Field &field)
{
    this->free = field.free;
    this->color = field.color;
}

bool Field::isFree()
{
    return this->free;
}