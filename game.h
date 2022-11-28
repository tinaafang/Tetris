#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <string>
#include "subject.h"
class CommandInterpreter;
class Board;

class Game: public Subject{
    int playerRound; // 0: curPlayer's round, 1: opponent's round
    int startLevel; // default level 0
    bool textMode;
    unsigned int seed;
    bool haveSeed;
    bool haveScript1;
    bool haveScript2;
    int hiScore;
    std::string scriptfile1;
    std::string scriptfile2;
    Board *curPlayer;
    Board *opponent;
    CommandInterpreter *cmdInter;

    public:
        explicit Game(int startLevel, bool textMode, unsigned int seed, bool haveSeed, bool haveScript1, bool haveScript2, std::string scriptfile1, std::string scriptfile2);
        int start();
        void left(int multiplier);
        void right(int multiplier);
        bool down(int multiplier);
        void rotate(bool clockwise, int multiplier);
        void drop(int multiplier);
        void IJL(char blockType, int multiplier);
        char getState(int row, int col) const override;
        int getLevel (int player) const override;
        int getScore (int player) const override;
        void noRandom(std::string file);
        void random();
        void levelUp(int multiplier);
        void levelDown(int multiplier);
        void restart();
        void blind();
        void heavy();
        void force(char blockType);
        ~Game();
};

#endif
