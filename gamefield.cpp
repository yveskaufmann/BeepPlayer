#include "gamefield.h"

GameField::GameField(int width, int height)
{
    this->width = width;
    this->height = height;

    this->fields = new Field *[height];
    for (int y = 0; y < height; y++)
    {
        this->fields[y] = new Field[width];
    }
};

bool GameField::isRowFull(int y)
{
    if (y <= 0 || y >= height)
    {
        return false;
    }

    for (int x = 0; x < width; x++)
    {
        if (this->isFree(x, y))
        {
            return false;
        }
    }

    return true;
}

void GameField::eraseRow(int y)
{

    for (int x = 0; x < width; x++)
    {
        fields[y][x].free = false;
        fields[y][x].erase();
    }
}

int GameField::eraseFullRows()
{

    int fullRowCount = 0;

    for (int y = 0; y < width; y++)
    {
        if (this->isRowFull(y))
        {
            this->eraseRow(y);
            y++;
        }
    }

    return fullRowCount;
}

Field &GameField::getField(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
    }

    return fields[y][x];
}

void GameField::setField(int x, int y, Field &field)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return;
    }

    fields[y][x] = field;
}

bool GameField::isFree(int x, int y)
{
    return getField(x, y).isFree();
}