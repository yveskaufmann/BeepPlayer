#ifndef BLOCK_H_
#define BLOCK_H_

#include <cstdint>
#include <vector>
#include "color.h"

class Position
{
public:
    int x;
    int y;

    Position();
    Position(int x, int y);
    Position(Position &pos);
};

class Block
{
public:
    Position pos;
    Position movement;
    Color color;
};

class BlockGroup
{
public:
    std::vector<Block> blocks;
};

#endif
