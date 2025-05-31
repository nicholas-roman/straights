#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "card.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "game.h"
#include "deck.h"
using namespace std;

int main(int argc, char *argv[])
{
    char identity;
    const int player_num = 4; // Number of players
    const int card_num = 13;  // Number of cards each player receives
    vector<Player *> players;
    vector<Card *> cards;

    for (int i = 0; i < player_num; ++i) // Creating cards and placing them at back of deck
    {
        for (int j = 1; j < card_num + 1; ++j)
        {
            Card *c = new Card(static_cast<Rank>(j), static_cast<Suit>(i));
            cards.emplace_back(c);
        }
    }

    unsigned num;

    if (argc > 1) // determining seed if one is given
    {
        try
        {
            num = stoi(string{argv[1]});
        }
        catch (invalid_argument &e)
        {
            cerr << e.what() << endl;
            return 0;
        }
        catch (std::out_of_range &e)
        {
            cerr << e.what() << endl;
            return 0;
        }
    }
    else
    {
        num = 0;
    }

    Deck *d = new Deck(cards);

    d->shuffle(argc, num);
    d->set_initial_shuffle();

    for (int i = 0; i < player_num; ++i) // Inviting players to play and determining if human or computer
    {
        cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << endl;
        cin >> identity;

        if (identity == 'h')
        {
            Human *player = new Human();
            player->set_identity(identity);
            player->set_score(0);
            players.emplace_back(player);
        }
        else if (identity == 'c')
        {
            Computer *player = new Computer();
            player->set_identity(identity);
            player->set_score(0);
            players.emplace_back(player);
        }
        else
        {
            cout << "Please input only h (human) or c (computer)" << endl;
            --i;
        }
    }

    // creating playing_deck for each deck that will be displayed on the table
    vector<Card *> clubs_cards;
    vector<Card *> diamonds_cards;
    vector<Card *> hearts_cards;
    vector<Card *> spades_cards;

    Deck *clubs = new Deck(clubs_cards);
    Deck *diamonds = new Deck(diamonds_cards);
    Deck *hearts = new Deck(hearts_cards);
    Deck *spades = new Deck(spades_cards);

    Game *straights = new Game(players, *d, *clubs, *diamonds, *hearts, *spades);
    cin.ignore();
    straights->play_game(argc, num); // Starting actual game (where all gameplay happens)

    // memory clean up
    for (int i = 0; i < players.size(); ++i)
    {
        delete players[i];
    }

    for (int i = 0; i < cards.size(); ++i)
    {
        delete cards[i];
    }

    delete straights;
    delete clubs;
    delete diamonds;
    delete hearts;
    delete spades;
    delete d;
}