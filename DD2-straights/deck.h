#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <string>
#include "suit.h"
#include "rank.h"

class Card;
class Player;

class Deck
{
    std::vector<Card *> initial_shuffle;
    std::vector<Card *> playing_deck;

public:
    Deck(std::vector<Card *> playing_deck);
    void shuffle(int seed, int num);
    void deal(std::vector<Player *> &players);
    void restore();
    void display_deck();
    void display_line();
    std::vector<Card *> get_deck();
    void set_deck(std::vector<Card *> d);
    void clear_playing_deck();
    void set_initial_shuffle();
};

#endif