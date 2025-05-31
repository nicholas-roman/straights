#include "deck.h"
#include "card.h"
#include "player.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// Constructor
Deck::Deck(std::vector<Card *> playing_deck) : playing_deck{playing_deck} {}

// shuffles the cards
void Deck::shuffle(int argc, int num)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    if (argc > 1)
    {
        seed = num;
    }

    std::default_random_engine rng{seed};

    for (int i = 0; i < 1000; i++)
    {
        std::shuffle(playing_deck.begin(), playing_deck.end(), rng);
    }
}

// deals out the cards to all four players in the game
void Deck::deal(vector<Player *> &players)
{
    int card = 0;

    for (int i = 0; i < 4; ++i)
    {
        vector<Card *> dealt_cards;
        for (int j = 0; j < 13; ++j) // places 13 cards at a time inside of each players hand
        {
            dealt_cards.emplace_back(playing_deck[card]);
            ++card;
        }
        players[i]->set_hand(dealt_cards);
    }
}

// restores the playing deck back to its initial shuffled position
void Deck::restore()
{
    playing_deck = initial_shuffle;
}

// prints out the entire deck
void Deck::display_deck()
{
    for (int i = 0; i < playing_deck.size(); ++i)
    {
        if ((i != 0) && (i != 13) && (i != 26) && (i != 39))
        {
            cout << " ";
        }

        playing_deck[i]->print_card();

        if ((i == 12) || (i == 25) || (i == 38) || (i == 51))
        {
            cout << endl;
        }
    }
}

// prints out the Clubs, Diamonds, Hearts, or Spades deck that is on the table
void Deck::display_line()
{
    for (int i = 0; i < playing_deck.size(); ++i)
    {
        Rank r = playing_deck[i]->get_rank();
        cout << " ";

        if (r == Rank::ACE)
        {
            cout << 'A';
        }
        else if (r == Rank::TWO)
        {
            cout << 2;
        }
        else if (r == Rank::THREE)
        {
            cout << 3;
        }
        else if (r == Rank::FOUR)
        {
            cout << 4;
        }
        else if (r == Rank::FIVE)
        {
            cout << 5;
        }
        else if (r == Rank::SIX)
        {
            cout << 6;
        }
        else if (r == Rank::SEVEN)
        {
            cout << 7;
        }
        else if (r == Rank::EIGHT)
        {
            cout << 8;
        }
        else if (r == Rank::NINE)
        {
            cout << 9;
        }
        else if (r == Rank::TEN)
        {
            cout << 'T';
        }
        else if (r == Rank::JACK)
        {
            cout << 'J';
        }
        else if (r == Rank::QUEEN)
        {
            cout << 'Q';
        }
        else
        {
            cout << 'K';
        }
    }
}

// sets the shuffled deck equal to the playing deck before starting the game
void Deck::set_initial_shuffle()
{
    initial_shuffle = playing_deck;
}

// returns a vector of Card pointers
std::vector<Card *> Deck::get_deck()
{
    return playing_deck;
}

// sets the playing deck equal to d
void Deck::set_deck(std::vector<Card *> d)
{
    playing_deck.clear();
    for (int i = 0; i < d.size(); ++i)
    {
        playing_deck.emplace_back(d[i]);
    }
}

// clears the playing deck
void Deck::clear_playing_deck()
{
    playing_deck.clear();
}
