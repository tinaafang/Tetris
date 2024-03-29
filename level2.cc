#include "level2.h"
#include "block.h"
#include <string>
#include <cstdlib>

void Level2::setL0File(std::string L0File) {}
void Level2::setNoRandom(bool noRandom, std::string noRandomFile) {}

std::unique_ptr<Block> Level2::CreateNextBlock()
{
    std::unique_ptr<Block> nextBlock;

    // random is a random int from 1 to 7
    int random = 1 + std::rand() / ((RAND_MAX + 1u) / 7);

    switch (random)
    {
    case 1:
        nextBlock = Level::CreateBlock(2, 'S');
        break;
    case 2:
        nextBlock = Level::CreateBlock(2, 'Z');
        break;
    case 3:
        nextBlock = Level::CreateBlock(2, 'I');
        break;
    case 4:
        nextBlock = Level::CreateBlock(2, 'J');
        break;
    case 5:
        nextBlock = Level::CreateBlock(2, 'T');
        break;
    case 6:
        nextBlock = Level::CreateBlock(2, 'O');
        break;
    case 7:
        nextBlock = Level::CreateBlock(2, 'L');
        break;
    } // switch

    return nextBlock;
}

Level2::~Level2() {}
