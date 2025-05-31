#ifndef _GAME_H_
#define _GAME_H_
#include "player.h"
#include "deck.h"
#include "computer.h"
#include "human.h"

class Game
{
    std::vector<Player *> &players;
    Deck playing_deck;
    Deck clubs;
    Deck diamonds;
    Deck hearts;
    Deck spades;

public:
    Game(std::vector<Player *> &players, Deck &playing_deck, Deck &clubs, Deck &diamonds, Deck &hearts, Deck &spades);
    bool score(std::vector<Player *> &players);
    void play_game(int argc, int seed);
    std::vector<Card *> legal(Player &p, bool first_turn);
    bool command(int turn, std::vector<Card *> legal_moves, std::vector<Card *> &loose_cards);
    void display_table();
    void table_place(Card *c);
    Player *convert(Player *p);
};

#endif