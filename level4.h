#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Block;

class Level4 : public Level
{
    bool noRandomBool;
    std::string noRandomFile;
    int noRandomFileIndex;
    std::vector<char> noRandomFileContent;

public:
    Level4(std::vector<std::vector<std::shared_ptr<Cell>>> cells)
        : Level{cells}, noRandomBool{false}, noRandomFile{""}, noRandomFileIndex{0}, noRandomFileContent{std::vector<char>{' '}}
    {
    }
    void setL0File(std::string L0File = "") override;
    void setNoRandom(bool noRandom, std::string noRandomFile = "") override;
    std::unique_ptr<Block> CreateNextBlock() override;
    ~Level4() override;
};

#endif
