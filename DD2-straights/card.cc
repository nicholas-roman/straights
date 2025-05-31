#include "card.h"
#include <iostream>
using namespace std;

// Card constructor
Card::Card(Rank card_rank, Suit card_suit) : card_rank{card_rank}, card_suit{card_suit} {}

// returns the cards rank
Rank Card::get_rank()
{
    return card_rank;
}

// returns the cards suit
Suit Card::get_suit()
{
    return card_suit;
}

// prints out the card
void Card::print_card()
{
    if (card_rank == Rank::ACE)
    {
        cout << 'A';
    }
    else if (card_rank == Rank::TWO)
    {
        cout << 2;
    }
    else if (card_rank == Rank::THREE)
    {
        cout << 3;
    }
    else if (card_rank == Rank::FOUR)
    {
        cout << 4;
    }
    else if (card_rank == Rank::FIVE)
    {
        cout << 5;
    }
    else if (card_rank == Rank::SIX)
    {
        cout << 6;
    }
    else if (card_rank == Rank::SEVEN)
    {
        cout << 7;
    }
    else if (card_rank == Rank::EIGHT)
    {
        cout << 8;
    }
    else if (card_rank == Rank::NINE)
    {
        cout << 9;
    }
    else if (card_rank == Rank::TEN)
    {
        cout << 'T';
    }
    else if (card_rank == Rank::JACK)
    {
        cout << 'J';
    }
    else if (card_rank == Rank::QUEEN)
    {
        cout << 'Q';
    }
    else
    {
        cout << 'K';
    }

    if (card_suit == Suit::CLUB)
    {
        cout << 'C';
    }
    else if (card_suit == Suit::DIAMOND)
    {
        cout << 'D';
    }
    else if (card_suit == Suit::HEART)
    {
        cout << 'H';
    }
    else
    {
        cout << 'S';
    }
}