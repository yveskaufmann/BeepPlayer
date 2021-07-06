#include "block.h"

Position::Position() : Position(0, 0)
{
}

Position::Position(Position &pos) : Position(pos.x, pos.y)
{
}

Position::Position(int x, int y) : x(x), y(y)
{
}