#ifndef TBLOCK_H
#define TBLOCK_H
#include "block.h"

class TBlock : public Block
{
public:
    TBlock(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType) : Block{cell1, cell2, cell3, cell4, alive, level, blockType} {};
    void rotate(bool clockwise);
};

#endif
