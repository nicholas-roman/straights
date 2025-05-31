#include "computer.h"
#include "deck.h"
#include <iostream>
#include <string>
using namespace std;

// plays as a computer player by playing first legal move
Card *Computer::play(std::vector<Card *> legal_moves)
{
    Card *c = legal_moves[0];
    c->print_card();
    int idx;

    for (int i = 0; i < hand.size(); ++i)
    {
        Suit s = hand[i]->get_suit();
        Rank r = hand[i]->get_rank();

        if ((s == c->get_suit()) && (r == c->get_rank()))
        {
            idx = i;
            break;
        }
    }

    hand.erase(hand.begin() + idx);
    return c;
}

// discards a card from the players hand
void Computer::discard(Card *c)
{
    c->print_card();
    discarded.emplace_back(c);
    hand.erase(hand.begin());
}
