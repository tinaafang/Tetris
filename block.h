#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Cell;

class Block
{
protected:
    std::vector<Cell *> components;
    int level;
    int alive;
    bool checkCell(char dir, Cell *cell);
    bool move(char dir);
    char blockType;
    bool horizontal;
    int topLeftRow;
    int topLeftCol;

public:
    Block(Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4, int alive, int level, char blockType);
    void left(bool isHeavy);
    void right(bool isHeavy);
    bool down();
    bool getHorizontal();
    void setHorizontal(bool horizontal);
    // virtual void rotate(bool clockwise) = 0;
    char getBlockType();
    int getLevel();
    void drop();
    int getAlive();
    int setAlive(int alive);
    bool member(Cell *cellPtr);
    int getTopLeftRow();
    int getTopLeftCol();
    void setTopLeftRow(int row);
    void setTopLeftCol(int col);
};

#endif
