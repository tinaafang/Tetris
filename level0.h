#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Block;

class Level0 : public Level
{
    std::string L0File;
    int L0FileIndex;
    std::vector<char> L0FileContent;

public:
    Level0(bool seedBool, unsigned int seed, std::vector<std::vector<Cell *>> cells)
        : Level{seedBool, seed, cells}, L0File{""}, L0FileIndex{0}, L0FileContent{std::vector<char>{' '}}
    {
    }
    Block *CreateNextBlock() override;
    void setL0File(std::string L0File = "");
    ~Level0() override;
};

#endif
