#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "field.h"
#include "color.h"

class GameField
{
private:
    int height;
    int width;
    Field **fields;

public:
    GameField(int width, int height);

    bool isRowFull(int y);
    void eraseRow(int y);
    void moveRow(int fromRow, int toRow);

    int eraseFullRows();

    void setField(int x, int y, Field &field);
    Field &getField(int x, int y) const;

    bool isFree(int x, int y);
};

#endif