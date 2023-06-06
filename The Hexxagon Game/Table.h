#ifndef THE_HEXXAGON_GAME_TABLE_H
#define THE_HEXXAGON_GAME_TABLE_H

#include <iostream>
#include <map>
#include <array>
#include "Player.h"

class Table {
private:
    //VARIABLES
    Player player1;
    Player player2;
    int pawns1;
    int pawns2;
    std::vector<std::vector<char>> table;
    std::map<std::array<int, 2>, char> pawns;
public:
    bool endGame;
    Player winner;
    //CONSTRUCTOR
    Table(Player player1, Player player2);
    //DESTRUCTOR
    virtual ~Table();

    //FUNCTIONS
    void update();
    void checkEndGame();
    void print();
    std::map<std::array<int, 2>, char> getPawns();
    void addPawn(int x, int y, char c);
    void removePawn(int x, int y);
    bool isAdjacent(int x1, int y1, int x2, int y2);
    bool isFarAdjacent(int x1, int y1, int x2, int y2);
    bool isValidMove(int x1, int y1, int x2, int y2, Player player);
    bool isValidPosition(int x, int y, Player player);
    Player getPlayer1();
    Player getPlayer2();
};


#endif //THE_HEXXAGON_GAME_TABLE_H
