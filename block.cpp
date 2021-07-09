#include "block.h"
#include "color.h"

Position::Position() : Position(0, 0)
{
}

Position::Position(const Position &pos) : Position(pos.x, pos.y)
{
}

Position::Position(int x, int y) : x(x), y(y)
{
}

Block::Block(const Color &color, const std::initializer_list<uint16_t> &rotations) : color(color)
{
    int i = 0;
    for (auto rotation : rotations)
    {
        this->rotations[i++] = rotation;
    }
}

std::vector<Position> Block::getPositions(int rotationIdx)
{
    return this->getPositions(rotationIdx, Position(0, 0));
}

std::vector<Position> Block::getPositions(int rotationIdx, const Position &offset)
{
    std::vector<Position> positions;

    uint16_t rotation = this->rotations[rotationIdx];
    uint16_t mask = 0x8000;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (rotation & mask)
            {
                positions.push_back(Position(x + offset.x - 1, y + offset.y));
            }

            mask = mask >> 1;
        }
    }

    return positions;
}

Block const Block::BLOCK_I = Block(
    Color::Cyan,
    {0x0F00, 0x2222, 0x00F0, 0x4444});

Block const Block::BLOCK_J = Block(
    Color::Blue,
    {0x8E00, 0x6440, 0x0E20, 0x44C0});

Block const Block::BLOCK_L = Block(
    Color::Orange,
    {0x2E00, 0x4460, 0x0E80, 0xC440});

Block const Block::BLOCK_O = Block(
    Color::Yellow,
    {0x6600, 0x6600, 0x6600, 0x6600});

Block const Block::BLOCK_S = Block(
    Color::Green,
    {0x6C00, 0x4620, 0x06C0, 0x8c40});

Block const Block::BLOCK_T = Block(
    Color::Purple,
    {0x4E00, 0x4640, 0x0E40, 0x4C40});

Block const Block::BLOCK_Z = Block(
    Color::Red,
    {0xC600, 0x2640, 0x0C60, 0x4C80});