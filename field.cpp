#include "field.h"
#include "color.h"

const Field Field::Empty = Field();

Field::Field() : free(false)
{
}

void Field::erase()
{
    this->free = true;
}

bool Field::isFree()
{
    return this->free;
}