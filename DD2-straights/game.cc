#include "game.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <utility>
using namespace std;

Game::Game(std::vector<Player *> &players, Deck &playing_deck, Deck &clubs, Deck &diamonds, Deck &hearts, Deck &spades) : players{players}, playing_deck{playing_deck}, clubs{clubs}, diamonds{diamonds}, hearts{hearts}, spades{spades} {}

// calculates the players score, and determines if a player surpasses 80 points
bool Game::score(vector<Player *> &players)
{
    bool game_over = false;
    vector<int> scores;
    int lowest_score = 80;
    int ending_score = 80;
    int winner;
    for (int i = 0; i < players.size(); ++i)
    {
        cout << "Player" << i + 1 << "'s discards:";
        players[i]->print_cards(players[i]->get_discarded());
        cout << endl
             << "Player" << i + 1 << "'s score: " << players[i]->get_score();

        players[i]->calc_score();

        cout << " = " << players[i]->get_score() << endl;
        players[i]->clear_discarded();
    }

    for (int i = 0; i < 4; ++i)
    {
        int p_score = players[i]->get_score();
        scores.emplace_back(p_score);

        if (p_score >= ending_score)
        {
            game_over = true;
        }

        if (p_score <= lowest_score)
        {
            lowest_score = p_score;
            winner = i + 1;
        }
    }

    if (game_over)
    {
        int lowest_count = count(scores.begin(), scores.end(), lowest_score);
        if (lowest_count > 1)
        {
            for (int i = 0; i < scores.size(); ++i)
            {
                if (scores[i] == lowest_score)
                {
                    cout << "Player" << i + 1 << " wins!" << endl;
                }
            }
        }
        else
        {
            cout << "Player" << winner << " wins!" << endl;
        }
    }
    return game_over;
}

// starts the game by determining who the first player is
int start(vector<Player *> players)
{
    vector<Card *> hand;
    for (int i = 0; i < players.size(); ++i)
    {
        hand = players[i]->get_hand();
        for (int j = 0; j < 13; ++j)
        {
            Rank r = hand[j]->get_rank();
            Suit s = hand[j]->get_suit();

            if ((r == Rank::SEVEN) && (s == Suit::SPADE))
            {
                return i;
            }
        }
    }
}

// places the given card, c, on the table (in either Clubs, Diamonds, Hearts, or Spades deck)
void Game::table_place(Card *c)
{
    Suit s = c->get_suit();
    int rank_val = static_cast<int>(c->get_rank());
    int first_card;
    int last_card;

    if (s == Suit::CLUB)
    {
        vector<Card *> cdeck = clubs.get_deck();
        if (cdeck.empty())
        {
            cdeck.emplace_back(c);
        }
        else
        {
            Card *first_club_card = *cdeck.begin();
            first_card = static_cast<int>(first_club_card->get_rank());

            Card *last_club_card = cdeck.back();
            last_card = static_cast<int>(last_club_card->get_rank());
            if (rank_val == first_card - 1)
            {
                cdeck.insert(cdeck.begin(), c);
            }
            else
            {
                cdeck.emplace_back(c);
            }
        }
        clubs.set_deck(cdeck);
    }
    else if (s == Suit::DIAMOND)
    {
        vector<Card *> ddeck = diamonds.get_deck();
        if (ddeck.empty())
        {
            ddeck.emplace_back(c);
        }
        else
        {
            Card *first_diamond_card = *ddeck.begin();
            first_card = static_cast<int>(first_diamond_card->get_rank());

            Card *last_diamond_card = ddeck.back();
            last_card = static_cast<int>(last_diamond_card->get_rank());

            if (rank_val == first_card - 1)
            {
                ddeck.insert(ddeck.begin(), c);
            }
            else
            {
                ddeck.emplace_back(c);
            }
        }
        diamonds.set_deck(ddeck);
    }
    else if (s == Suit::HEART)
    {
        vector<Card *> hdeck = hearts.get_deck();
        if (hdeck.empty())
        {
            hdeck.emplace_back(c);
        }
        else
        {
            Card *first_heart_card = *hdeck.begin();
            first_card = static_cast<int>(first_heart_card->get_rank());

            Card *last_heart_card = hdeck.back();
            last_card = static_cast<int>(last_heart_card->get_rank());

            if (rank_val == first_card - 1)
            {
                hdeck.insert(hdeck.begin(), c);
            }
            else
            {
                hdeck.emplace_back(c);
            }
        }
        hearts.set_deck(hdeck);
    }
    else
    {
        vector<Card *> sdeck = spades.get_deck();
        if (sdeck.empty())
        {
            sdeck.emplace_back(c);
        }
        else
        {
            Card *first_spade_card = *sdeck.begin();
            first_card = static_cast<int>(first_spade_card->get_rank());

            Card *last_spade_card = sdeck.back();
            last_card = static_cast<int>(last_spade_card->get_rank());

            if (rank_val == first_card - 1)
            {
                sdeck.insert(sdeck.begin(), c);
            }
            else
            {
                sdeck.emplace_back(c);
            }
        }
        spades.set_deck(sdeck);
    }
}

// Main function for the entire game play
void Game::play_game(int argc, int seed)
{
    bool game_over = false;
    vector<Card *> loose_cards;

    while (game_over == false)
    {
        bool first_turn = true;
        int count_turn = 0;

        playing_deck.shuffle(argc, seed);
        playing_deck.set_initial_shuffle();
        playing_deck.deal(players);

        int player_turn = start(players);

        cout << "A new round begins. It's Player" << player_turn + 1 << "'s turn to play." << endl;

        while (1)
        {
            if (player_turn > 3)
            {
                player_turn = 0;
            }

            vector<Card *> game_deck = playing_deck.get_deck();

            if (count_turn == game_deck.size())
            {
                break;
            }

            vector<Card *> legal_moves;
            vector<Card *> p_hand = players[player_turn]->get_hand();

            if (players[player_turn]->get_identity() == 'h')
            {
                display_table();
                cout << "Your hand:";
                players[player_turn]->print_cards(p_hand);
                cout << endl
                     << "Legal plays:";

                legal_moves = legal(*players[player_turn], first_turn);

                for (int i = 0; i < legal_moves.size(); ++i)
                {
                    cout << " ";
                    legal_moves[i]->print_card();
                }
                cout << endl;
                game_over = command(player_turn, legal_moves, loose_cards);
            }
            else
            {
                legal_moves = legal(*players[player_turn], first_turn);

                if (legal_moves.empty())
                {
                    cout << "Player" << player_turn + 1 << " discards ";
                    players[player_turn]->discard(p_hand[0]);
                    cout << "." << endl;
                }
                else
                {
                    cout << "Player" << player_turn + 1 << " plays ";
                    Card *c = players[player_turn]->play(legal_moves);
                    cout << "." << endl;
                    table_place(c);
                }
            }

            if (game_over)
            {
                break;
            }

            legal_moves.clear();
            ++player_turn;
            ++count_turn;
            first_turn = false;
        }

        if (game_over)
        {
            break;
        }

        game_over = score(players);
        playing_deck.set_initial_shuffle();
        clubs.clear_playing_deck();
        diamonds.clear_playing_deck();
        hearts.clear_playing_deck();
        spades.clear_playing_deck();
    }
    clubs.clear_playing_deck();
    diamonds.clear_playing_deck();
    hearts.clear_playing_deck();
    spades.clear_playing_deck();

    for (int i = 0; i < loose_cards.size(); ++i)
    {
        delete loose_cards[i];
    }
}

// determines what moves are legal and then returns a list of legal moves that can be made by the player
vector<Card *> Game::legal(Player &p, bool first_turn)
{
    vector<Card *> legal_moves;
    vector<Card *> p_hand = p.get_hand();

    if (first_turn)
    {
        for (int i = 0; i < p_hand.size(); ++i)
        {
            if ((p_hand[i]->get_rank() == Rank::SEVEN) && (p_hand[i]->get_suit() == Suit::SPADE))
            {
                legal_moves.emplace_back(p_hand[i]);
                return legal_moves;
            }
        }
    }

    for (int i = 0; i < p_hand.size(); ++i)
    {
        Rank r = p_hand[i]->get_rank();
        Suit s = p_hand[i]->get_suit();

        if (r == Rank::SEVEN)
        {
            legal_moves.emplace_back(p_hand[i]);
            continue;
        }

        int rank_val = static_cast<int>(r);
        int first_card;
        int last_card;

        vector<Card *> cdeck = clubs.get_deck();
        vector<Card *> ddeck = diamonds.get_deck();
        vector<Card *> hdeck = hearts.get_deck();
        vector<Card *> sdeck = spades.get_deck();

        if ((s == Suit::CLUB) && (!cdeck.empty()))
        {
            Card *first_club_card = *cdeck.begin();
            first_card = static_cast<int>(first_club_card->get_rank());

            Card *last_club_card = cdeck.back();
            last_card = static_cast<int>(last_club_card->get_rank());

            if ((rank_val == first_card - 1) || (rank_val == last_card + 1))
            {
                legal_moves.emplace_back(p_hand[i]);
            }
        }
        else if ((s == Suit::DIAMOND) && (!ddeck.empty()))
        {
            Card *first_diamond_card = *ddeck.begin();
            first_card = static_cast<int>(first_diamond_card->get_rank());

            Card *last_diamond_card = ddeck.back();
            last_card = static_cast<int>(last_diamond_card->get_rank());

            if ((rank_val == first_card - 1) || (rank_val == last_card + 1))
            {
                legal_moves.emplace_back(p_hand[i]);
            }
        }
        else if ((s == Suit::HEART) && (!hdeck.empty()))
        {
            Card *first_heart_card = *hdeck.begin();
            first_card = static_cast<int>(first_heart_card->get_rank());

            Card *last_heart_card = hdeck.back();
            last_card = static_cast<int>(last_heart_card->get_rank());

            if ((rank_val == first_card - 1) || (rank_val == last_card + 1))
            {
                legal_moves.emplace_back(p_hand[i]);
            }
        }
        else if ((s == Suit::SPADE) && (!sdeck.empty()))
        {
            Card *first_spade_card = *sdeck.begin();
            first_card = static_cast<int>(first_spade_card->get_rank());

            Card *last_spade_card = sdeck.back();
            last_card = static_cast<int>(last_spade_card->get_rank());

            if ((rank_val == first_card - 1) || (rank_val == last_card + 1))
            {
                legal_moves.emplace_back(p_hand[i]);
            }
        }
    }
    return legal_moves;
}

// converts a given character to a suit and returns the suit
Suit suit_convert(char c)
{
    Suit s;
    if (c == 'C')
    {
        s = Suit::CLUB;
    }
    else if (c == 'D')
    {
        s = Suit::DIAMOND;
    }
    else if (c == 'H')
    {
        s = Suit::HEART;
    }
    else
    {
        s = Suit::SPADE;
    }
    return s;
}

// converts a given char to a rank and returns the rank
Rank rank_convert(char c)
{
    Rank r;
    if (c == 'A')
    {
        r = Rank::ACE;
    }
    else if (c == '2')
    {
        r = Rank::TWO;
    }
    else if (c == '3')
    {
        r = Rank::THREE;
    }
    else if (c == '4')
    {
        r = Rank::FOUR;
    }
    else if (c == '5')
    {
        r = Rank::FIVE;
    }
    else if (c == '6')
    {
        r = Rank::SIX;
    }
    else if (c == '7')
    {
        r = Rank::SEVEN;
    }
    else if (c == '8')
    {
        r = Rank::EIGHT;
    }
    else if (c == '9')
    {
        r = Rank::NINE;
    }
    else if (c == 'T')
    {
        r = Rank::TEN;
    }
    else if (c == 'J')
    {
        r = Rank::JACK;
    }
    else if (c == 'Q')
    {
        r = Rank::QUEEN;
    }
    else if (c == 'K')
    {
        r = Rank::KING;
    }
    return r;
}

// receives user input from a human player and all of their possible commands
bool Game::command(int turn, vector<Card *> legal_moves, vector<Card *> &loose_cards)
{
    bool stay = true;
    vector<Card *> p_hand = players[turn]->get_hand();

    do
    {
        string line;
        string com;
        getline(cin, line);
        istringstream ss{line};

        while (ss >> com)
        {
            line = "";
            if (com == "play")
            {
                char rank_val;
                char suit;

                ss >> rank_val;
                ss >> suit;
                bool in_legal = false;

                if (legal_moves.empty())
                {
                    cout << "It seems you do not have any legal moves. Please enter another command." << endl;
                }
                else
                {
                    while (in_legal == false)
                    {
                        Suit s = suit_convert(suit);
                        Rank r = rank_convert(rank_val);
                        Card *c = new Card(r, s);
                        loose_cards.emplace_back(c);

                        for (int i = 0; i < legal_moves.size(); ++i)
                        {
                            if ((r == legal_moves[i]->get_rank()) && (s == legal_moves[i]->get_suit()))
                            {
                                in_legal = true;
                                break;
                            }
                        }

                        if (in_legal)
                        {

                            int idx;

                            for (int i = 0; i < p_hand.size(); ++i)
                            {
                                Suit s = p_hand[i]->get_suit();
                                Rank r = p_hand[i]->get_rank();

                                if ((s == c->get_suit()) && (r == c->get_rank()))
                                {
                                    idx = i;
                                    break;
                                }
                            }

                            p_hand.erase(p_hand.begin() + idx);
                            players[turn]->set_hand(p_hand);
                            cout << "Player" << turn + 1 << " plays ";
                            c->print_card();
                            cout << "." << endl;
                            table_place(c);
                            stay = false;
                        }
                        else
                        {
                            cout << "This is not a legal play." << endl;
                            break;
                        }
                    }
                }
            }
            else if (com == "discard")
            {
                char rank_val;
                char suit;
                ss >> rank_val;
                ss >> suit;

                if (legal_moves.empty())
                {
                    Suit s = suit_convert(suit);
                    Rank r = rank_convert(rank_val);
                    Card *c = new Card(r, s);
                    cout << "Player" << turn + 1 << " discards ";
                    players[turn]->discard(c);
                    cout << "." << endl;
                    stay = false;
                    loose_cards.emplace_back(c);
                }
                else
                {
                    cout << "You have a legal play. You may not discard." << endl;
                }
            }
            else if (com == "deck")
            {
                playing_deck.display_deck();
            }
            else if (com == "quit")
            {
                return true;
            }
            else if (com == "ragequit")
            {
                players[turn] = convert(players[turn]);
                cout << "Player" << turn + 1 << " ragequits. A computer will now takeover." << endl;
                stay = false;

                if (legal_moves.empty())
                {
                    cout << "Player" << turn + 1 << " discards ";
                    players[turn]->discard(p_hand[0]);
                    cout << "." << endl;
                }
                else
                {
                    cout << "Player" << turn + 1 << " plays ";
                    Card *c = players[turn]->play(legal_moves);
                    cout << "." << endl;
                    table_place(c);
                }
            }
            else
            {
                cout << "Improper command. Please try again." << endl;
                continue;
            }
        }
    } while (stay);
    return false;
}

// converts a player from a human to a computer
Player *Game::convert(Player *p)
{
    Player *new_p = new Computer();
    new_p->set_identity('c');
    new_p->set_score(p->get_score());
    vector<Card *> p_hand = p->get_hand();
    vector<Card *> new_p_hand;

    for (int i = 0; i < p_hand.size(); ++i)
    {
        new_p_hand.emplace_back(p_hand[i]);
    }

    new_p->set_hand(new_p_hand);

    vector<Card *> p_discarded = p->get_discarded();
    vector<Card *> new_p_discarded;

    for (int i = 0; i < p_discarded.size(); ++i)
    {
        new_p_discarded.emplace_back(p_discarded[i]);
    }
    new_p->set_discarded(new_p_discarded);
    delete p;
    return new_p;
}

// displays the table
void Game::display_table()
{
    cout << "Cards on the table:" << endl;

    cout << "Clubs:";
    clubs.display_line();

    cout << "\nDiamonds:";
    diamonds.display_line();

    cout << "\nHearts:";
    hearts.display_line();

    cout << "\nSpades:";
    spades.display_line();
    cout << endl;
}
