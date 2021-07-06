#ifndef FIELD_H_
#define FIELD_H_

#include "color.h"

class Field
{
public:
    static const Field Empty;

    bool free;

    Field();

    void erase();
    bool isFree();
};

#endif