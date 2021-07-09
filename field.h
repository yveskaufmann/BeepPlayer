#ifndef FIELD_H_
#define FIELD_H_

#include "color.h"

class Field
{
public:
    static const Field Empty;

    bool free;
    Color color;

    Field();

    void unset();
    void set(const Color &color);
    void setFrom(const Field &field);
    bool isFree();
};

#endif