#include "human.h"
#include "deck.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Card *Human::play(std::vector<Card *> legal_moves)
{
}

// discards a card by adding it to the discarded cards, and erasing it from the players hand
void Human::discard(Card *c)
{
    c->print_card();
    discarded.emplace_back(c);

    int idx;

    for (int i = 0; i < hand.size(); ++i)
    {
        if ((c->get_rank() == hand[i]->get_rank()) && (c->get_suit() == hand[i]->get_suit()))
        {
            idx = i;
            break;
        }
    }
    hand.erase(hand.begin() + idx);
}
