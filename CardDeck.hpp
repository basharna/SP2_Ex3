#ifndef CARDDECK_HPP
#define CARDDECK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

enum class Card
{
    MONOPOLY,
    ROAD_BUILDING,
    YEAR_OF_PLENTY,
    KNIGHT,
    VICTORY_POINT,
    EMPTY
};

class Player; 

class CardDeck
{
public:
    static CardDeck &getInstance();

    Card drawCard();
    void returnCard(Card card);

    static string cardToString(Card card);


private:
    CardDeck();
    vector<Card> deck;
    void initializeDeck();
    mt19937 rng;
};

#endif // CARD_HPP
