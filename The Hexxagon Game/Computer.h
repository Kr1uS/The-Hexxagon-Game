#ifndef THE_HEXXAGON_GAME_COMPUTER_H
#define THE_HEXXAGON_GAME_COMPUTER_H

#include <map>
#include "Player.h"

class Computer : public Player{
private:
    char c;
public:
    //CONSTRUCTOR
    Computer();
    //DESTRUCTOR
    ~Computer() override;

    void move(Table *table) override;
    std::array<int, 4> getPositions(Table *table) override;

};


#endif //THE_HEXXAGON_GAME_COMPUTER_H
