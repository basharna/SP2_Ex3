#include "Catan.hpp"

Catan::Catan(Player *player1, Player *player2, Player *player3) : player1(player1), player2(player2), player3(player3), cardDeck(CardDeck::getInstance())
{
    this->board = new Board();

    // set player ids
    this->player1->setPlayerID(1);
    this->player2->setPlayerID(2);
    this->player3->setPlayerID(3);

    // set players board
    this->player1->setBoard(this->board);
    this->player2->setBoard(this->board);
    this->player3->setBoard(this->board);

    // set game
    this->player1->setGame(this);
    this->player2->setGame(this);
    this->player3->setGame(this);

    // set turn
    this->player1->setTurn(true);
    this->player2->setTurn(false);
    this->player3->setTurn(false);
    this->currentPlayerTurn = 1;

    this->winner = nullptr;
}

Board *Catan::getBoard()
{
    return this->board;
}

CardDeck &Catan::getCardDeck()
{
    return this->cardDeck;
}

Player *Catan::getPlayer1()
{
    return this->player1;
}

Player *Catan::getPlayer2()
{
    return this->player2;
}

Player *Catan::getPlayer3()
{
    return this->player3;
}

vector<Player *> Catan::getPlayers()
{
    return {this->player1, this->player2, this->player3};
}

int Catan::getCurrentPlayerTurn()
{
    return this->currentPlayerTurn;
}

void Catan::checkWinner()
{
    Player *winner = nullptr;

    if (this->player1->getVictoryPoints() >= 10)
    {
        winner = this->player1;
    }
    else if (this->player2->getVictoryPoints() >= 10)
    {
        winner = this->player2;
    }
    else if (this->player3->getVictoryPoints() >= 10)
    {
        winner = this->player3;
    }

    if (winner != nullptr)
    {
        this->winner = winner;
        cout << "\nGame over! " << winner->getName() << " wins!" << endl;
        exit(0);
    }
}

void Catan::updateTurn(Player *player)
{
    int playerID = player->getPlayerID();

    // set next player turn
    if (currentPlayerTurn == 1 && playerID == 1)
    {
        this->player2->setTurn(true);
        currentPlayerTurn = 2;
    }
    else if (currentPlayerTurn == 2 && playerID == 2)
    {
        this->player3->setTurn(true);
        currentPlayerTurn = 3;
    }
    else if (currentPlayerTurn == 3 && playerID == 3)
    {
        this->player1->setTurn(true);
        currentPlayerTurn = 1;
    }

    checkWinner();
}

void Catan::printWinner()
{
    if (this->winner == nullptr)
    {
        cout << "No winner yet!" << endl;
    }
    else
    {
        cout << "The winner is: " << this->winner->getName() << endl;
    }
}

void Catan::chooseStartingPlayer()
{
    int random = rand() % 3 + 1;
    if (random == 1)
    {
        this->player1->setTurn(true);
        this->player2->setTurn(false);
        this->player3->setTurn(false);
        currentPlayerTurn = 1;
    }
    else if (random == 2)
    {
        this->player1->setTurn(false);
        this->player2->setTurn(true);
        this->player3->setTurn(false);
        currentPlayerTurn = 2;
    }
    else
    {
        this->player1->setTurn(false);
        this->player2->setTurn(false);
        this->player3->setTurn(true);
        currentPlayerTurn = 3;
    }
}

void Catan::setStartingPlayer(int id)
{
    if (id == 1)
    {
        this->player1->setTurn(true);
        this->player2->setTurn(false);
        this->player3->setTurn(false);
        this->currentPlayerTurn = 1;
    }
    else if (id == 2)
    {
        this->player1->setTurn(false);
        this->player2->setTurn(true);
        this->player3->setTurn(false);
        this->currentPlayerTurn = 2;
    }
    else
    {
        this->player1->setTurn(false);
        this->player2->setTurn(false);
        this->player3->setTurn(true);
        this->currentPlayerTurn = 3;
    }
}

void Catan::simulateDiceRoll(Player *p, int number)
{

    p->setHasRolled(true);

    // Iterate through all tiles on the board
    for (int i = 0; i <= 18; i++)
    {
        Tile *tile = this->board->getTile(i);
        if (tile == nullptr)
        {
            cout << "Tile not found" << endl;
            exit(1);
        }
        if (tile->getToken() == number)
        {
            for (auto &v : tile->getVertices())
            {
                if (v->hasBuilding())
                {
                    Building *building = v->getBuilding();
                    if (building->getType() == BuildingType::SETTLEMENT || building->getType() == BuildingType::STARTING_SETTLEMENT)
                    {
                        building->getOwner()->addResource(tile->getResource(), 1);
                    }
                    else if (building->getType() == BuildingType::CITY)
                    {
                        building->getOwner()->addResource(tile->getResource(), 2);
                    }
                }
            }
        }
    }
}
