#include <iostream>
#include "graphicsViewer.h"

const int rows = 20;
const int cols = 11;
const int dim = 20;

GraphicsViewer::GraphicsViewer(Game *subject) : subject{subject}, top{0}, bot{65}, left{0}, right{60}
{
    window = std::make_unique<Xwindow>((this->right - this->left + 1) * 10, (this->bot - this->top + 1) * 10);
    subject->attach(this);
}

GraphicsViewer::~GraphicsViewer()
{
    subject->detach(this);
    window = nullptr;
}

void GraphicsViewer::printTitle() {
    //print highest score
    window->fillRectangle(25, 0, 600, 90, window->White);
    window->drawString(200, 10, "Highest Score: " + std::to_string(subject->getHiScore()));

    //print player names
    window->drawString(20, 25, "Player1: " + subject->getName(0));
    window->drawString(300, 25, "Player2: " + subject->getName(1));

    //print player scores
    window->drawString(20, 40, "Score: " + std::to_string(subject->getScore(0)));
    window->drawString(300, 40, "Score: " + std::to_string(subject->getScore(1)));

    //print player bonus
    window->drawString(20, 55, "Bonus: " + std::to_string(subject->getBonus(0)));
    window->drawString(300, 55, "Bonus: " + std::to_string(subject->getBonus(1)));

    //print player level
    window->drawString(20, 70, "Level: " + std::to_string(subject->getLevel(0)));
    window->drawString(300, 70, "Level: " + std::to_string(subject->getLevel(1)));

    //print player status
    if (subject->getOver(0)) {
        window->drawString(20, 85, "Status: Dead");
    } else {
        window->drawString(20, 85, "Status: Alive");
    }
    if (subject->getOver(1)) {
        window->drawString(300, 85, "Status: Dead");
    } else {
        window->drawString(300, 85, "Status: Alive");
    }
}

void GraphicsViewer::prompt()
{
    // std::string promptStr = "Choose your special actions(heavy, blind, or force) and enter it on the command line:";
    // window->fillRectangle(2500, 70, 10, 30, window->White);
    // window->drawString(2500, 70, promptStr);
}

void GraphicsViewer::printPlayer(int row_start, int row_end, int x, int y, int player)
{
    int color;
    for (int i = row_start; i <= row_end; ++i)
    {
        for (int j = cols-1; j >= 0; --j)
        {
            bool change = subject->getChange(player, i, j);
            char output = subject->getState(player, i, j);

            if (change)
            {
                if (output == '*')
                {
                    color = window->Brown;
                }
                else if (output == 'S')
                {
                    color = window->Blue;
                }
                else if (output == 'J')
                {
                    color = window->Cyan;
                }
                else if (output == 'Z')
                {
                    color = window->Magenta;
                }
                else if (output == 'O')
                {
                    color = window->Red;
                }
                else if (output == 'T')
                {
                    color = window->Orange;
                }
                else if (output == 'I')
                {
                    color = window->Green;
                }
                else if (output == 'L')
                {
                    color = window->Yellow;
                }
                else if (output == '?')
                {
                    color = window->White;
                }
                else if (output == ' ')
                {
                    if (i >= 18)
                    {
                        color = window->White;
                    }
                    else
                    {
                        color = window->Black;
                    }
                }
                window->fillRectangle(x + (dim * j), y + dim * (i - row_start), dim, dim, color);
                subject->setChange(player, i, j, 0);
            }
        }
    }
}


void GraphicsViewer::printSummary() {
    int p1Total = subject->getScore(0) + subject->getBonus(0);
    int p2Total = subject->getScore(1) + subject->getBonus(1);
    
    window->drawString(255, 10 ,"Game Over");
    window->drawString(246, 30 ,"Game Summary");
    window->drawString(180, 90, subject->getName(0) + "'s score: " + std::to_string(subject->getScore(0)) + "  bonus: " + std::to_string(subject->getBonus(0)) + " total: " + std::to_string(p1Total));
    window->drawString(180, 120, subject->getName(1) + "'s score: " + std::to_string(subject->getScore(1)) + "  bonus: " + std::to_string(subject->getBonus(1)) + " total: " + std::to_string(p2Total));
    if(subject->getOver(0) && subject->getOver(1)){
        if (p1Total > p2Total) {
            window->drawString(185, 150, "By comparing score, " + subject->getName(0) + " won!");
        } else if (p1Total < p2Total) {
            window->drawString(185, 150, "By comparing score, " + subject->getName(1) + " won!");
        } else {
            window->drawString(190, 150, "By comparing score, it's a Tie!");
        }
    }
    else if(subject->getOver(0) || subject->getOver(1)){
        if(subject->getOver(0)){
            window->drawString(255, 150, subject->getName(1) + " won!");
        }else if(subject->getOver(1)){
            window->drawString(255, 150, subject->getName(0) + " won!");
        }
    }
}

void GraphicsViewer::clear() {
    window->fillRectangle(0, 0, 600, 600, window->White);
}

void GraphicsViewer::notify(bool over)
{
    if (over) {
        window->fillRectangle(0, 0, 600, 600, window->White);
        printSummary();
        window->drawString(100, 200, "Enter ENDGAME to end the game or restart to restart the game");
        
    } else {
        printTitle();
        printPlayer(0, 17, 20, 100, 0);
        printPlayer(0, 17, 300, 100, 1);
        window->drawString(20, 500, "Next: ");
        window->drawString(300, 500, "Next: ");
        printPlayer(18, 19, 20, 510, 0);
        printPlayer(18, 19, 300, 510, 1);
    }
}
