#ifndef _CARD_H_
#define _CARD_H_
#include "suit.h"
#include "rank.h"
#include <vector>

class Card
{
    Rank card_rank;
    Suit card_suit;

public:
    Card(Rank card_rank, Suit card_suit);
    Rank get_rank();
    Suit get_suit();
    void print_card();
};

#endif