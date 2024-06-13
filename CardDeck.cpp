#include "CardDeck.hpp"
#include "Player.hpp"
#include <ctime>

CardDeck &CardDeck::getInstance()
{
    static CardDeck instance;
    return instance;
}

CardDeck::CardDeck() : rng(static_cast<unsigned int>(std::time(0)))
{
    initializeDeck();
}
void CardDeck::initializeDeck()
{
    deck.reserve(13); // 3 Knights + 6 Progress + 4 Victory Points

    for (int i = 0; i < 3; ++i)
    {
        deck.push_back(Card::KNIGHT);
    }

    for (int i = 0; i < 2; ++i)
    {
        deck.push_back(Card::ROAD_BUILDING);
        deck.push_back(Card::YEAR_OF_PLENTY);
        deck.push_back(Card::MONOPOLY);
    }

    for (int i = 0; i < 5; ++i)
    {
        deck.push_back(Card::VICTORY_POINT);
    }

    shuffle(deck.begin(), deck.end(), rng);
}

Card CardDeck::drawCard()
{
    if (deck.empty())
    {
        cout << "Deck is empty" << endl;
        return Card::EMPTY;
    }

    Card drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

void CardDeck::returnCard(Card card)
{
    deck.push_back(card);
    shuffle(deck.begin(), deck.end(), rng);
}

string CardDeck::cardToString(Card card)
{
    switch (card)
    {
    case Card::MONOPOLY:
        return "Monopoly";
    case Card::ROAD_BUILDING:
        return "Road Building";
    case Card::YEAR_OF_PLENTY:
        return "Year of Plenty";
    case Card::KNIGHT:
        return "Knight";
    case Card::VICTORY_POINT:
        return "Victory Point";
    case Card::EMPTY:
        return "Empty";
    }
    return "Invalid card";
}

