#include "player.h"
#include <vector>
#include <iostream>
using namespace std;

// places all of the dealt cards into the players hand
void Player::set_hand(vector<Card *> cards)
{
    hand = cards;
}

// returns the players hand
std::vector<Card *> Player::get_hand()
{
    return hand;
}

void Player::set_discarded(vector<Card *> cards)
{
    for (int i = 0; i < cards.size(); ++i)
    {
        discarded.emplace_back(cards[i]);
    }
}

void Player::clear_discarded()
{
    discarded.clear();
}

std::vector<Card *> Player::get_discarded()
{
    return discarded;
}

// prints out the cards
void Player::print_cards(vector<Card *> cards)
{
    for (int i = 0; i < cards.size(); ++i)
    {
        cout << " ";
        cards[i]->print_card();
    }
}

// returns the player identity (human or computer)
char Player::get_identity()
{
    return identity;
}

// sets the players identity
void Player::set_identity(char c)
{
    identity = c;
}

// calculates the players score
void Player::calc_score()
{
    int total = 0;

    for (int i = 0; i < discarded.size(); ++i)
    {
        int val = static_cast<int>(discarded[i]->get_rank());
        total += val;
    }
    cout << " + " << total;
    score += total;
}

// returns the players score
int Player::get_score()
{
    return score;
}

// sets the players score
void Player::set_score(int s)
{
    score = s;
}
