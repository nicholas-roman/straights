#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include "card.h"

class Card;

class Player
{
protected:
    char identity;
    int score;
    std::vector<Card *> hand;
    std::vector<Card *> discarded;

public:
    virtual Card *play(std::vector<Card *> legal_moves) = 0;
    virtual void discard(Card *c) = 0;

    std::vector<Card *> get_hand();
    void set_hand(std::vector<Card *> cards);

    std::vector<Card *> get_discarded();
    void set_discarded(std::vector<Card *> cards);
    void clear_discarded();

    char get_identity();
    void set_identity(char c);

    void print_cards(std::vector<Card *> cards);

    void calc_score();
    int get_score();
    void set_score(int score);
};

#endif