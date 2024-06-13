#ifndef CATAN_HPP
#define CATAN_HPP

#include "Board.hpp"
#include "Player.hpp"
#include "CardDeck.hpp"
#include <iostream>
#include <string>

using namespace std;

class Catan
{
public:
    static Catan &getInstance(Player *player1, Player *player2, Player *player3);

    // Getters
    Board *getBoard();
    CardDeck &getCardDeck();
    Player *getPlayer1();
    Player *getPlayer2();
    Player *getPlayer3();
    vector<Player *> getPlayers();

    void chooseStartingPlayer();

    // turn logic
    void updateTurn(Player *player);
    
    void printWinner();


private:
    Catan(Player *player1, Player *player2, Player *player3);

    Board *board;
    Player *player1;
    Player *player2;
    Player *player3;
    CardDeck &cardDeck;
    int currentPlayerTurn;
    Player *winner;

    // check if game is over
    void checkWinner();

};

#endif // CATAN_HPP