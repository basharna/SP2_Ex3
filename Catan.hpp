#ifndef CATAN_HPP
#define CATAN_HPP

#include "Board.hpp"
#include "Player.hpp"

class Catan {
public:
    static Catan& getInstance(Player* player1, Player* player2, Player* player3) {
        static Catan instance(player1, player2, player3);
        return instance;
    }


private:
    Catan(Player* player1, Player* player2, Player* player3) : player1(player1), player2(player2), player3(player3) {}

    Board* board;
    Player* player1;
    Player* player2;
    Player* player3;
};

#endif // CATAN_HPP