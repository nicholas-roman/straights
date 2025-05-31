#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <vector>
#include "player.h"

class Human : public Player
{
public:
    Card *play(std::vector<Card *> legal_moves) override;
    void discard(Card *c) override;
};

#endif