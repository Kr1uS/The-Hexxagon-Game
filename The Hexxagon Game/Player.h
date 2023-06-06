#ifndef THE_HEXXAGON_GAME_PLAYER_H
#define THE_HEXXAGON_GAME_PLAYER_H

#include <iostream>

class Table;

class Player {
private:
    char c;

public:
    //CONSTRUCTOR
    Player();
    //DESTRUCTOR
    virtual ~Player();

    //FUNCTIONS
    //Char getter-setter
    char getChar() const;
    void setChar(char c);

    virtual void move(Table *table);
    virtual std::array<int, 4> getPositions(Table *table);
};


#endif //THE_HEXXAGON_GAME_PLAYER_H
