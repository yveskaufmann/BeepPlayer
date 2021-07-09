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
    Position(const Position &pos);
    Position(int x, int y);
};

class Block
{
public:
    static const Block BLOCK_I;
    static const Block BLOCK_J;
    static const Block BLOCK_L;
    static const Block BLOCK_O;
    static const Block BLOCK_S;
    static const Block BLOCK_T;
    static const Block BLOCK_Z;

    Block(const Color &color, const std::initializer_list<uint16_t> &rotations);

    Color color;
    uint16_t rotations[4];

    std::vector<Position> getPositions(int rotation);
    std::vector<Position> getPositions(int rotation, const Position &offset);
};

#endif
