#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <vector>
#include "player.h"

class Computer : public Player
{
public:
    Card *play(std::vector<Card *> legal_moves) override;
    void discard(Card *c) override;
};

#endif