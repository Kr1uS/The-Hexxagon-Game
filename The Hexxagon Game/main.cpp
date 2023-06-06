#include <iostream>
#include "Table.h"
#include "Player.h"
#include "Computer.h"

//DECLARING FUNCTIONS
void showMessage(const std::string message);
char inputChar(std::string message);

void start();
void singlePlay();
void multiPlay();
int inputGameMode();

//MAIN FUNCTION
int main() {
    showMessage("!THE-HEXXAGON-GAME!");

    start();    //STARTING THE GAME HERE

    return 0;
}

//FUNCTIONS FOR INPUT/OUTPUT
void showMessage(const std::string message){
    int l = (65 - message.size())/2;
    for (int i = 0; i < l; i ++) std::cout << '-';
    std::cout << message;
    for (int i = 0; i < l; i ++) std::cout << '-';
    std::cout << '\n';
}
char inputChar(std::string message) {
    char c;
    showMessage(message);
    std::cout << ">> ";
    std::cin >> c;
    return c;
}

//START GAME
void start(){
    int option = inputGameMode();
    if (option == 1) singlePlay();
    if (option == 2) multiPlay();
}

//CHOOSE GAME MODE
int inputGameMode(){
    showMessage("Choose game mode");
    char option = inputChar("(1 - one player; 2 - two players)");
    if (option == '1') return 1;
    if (option == '2') return 2;
    else {
        showMessage("Invalid input");
        inputGameMode();
    }
}

//SINGLE-PLAY
void singlePlay(){
    Player *player = new Player();
    Player *computer = new Computer();

    player->setChar(inputChar("Set your pawn char:"));
    computer->setChar('c');

    Table *table = new Table(*player, *computer);
    table->print();

    while(!table->endGame) {
        player->move(table);
        table->print();
        computer->move(table);
        table->print();
    }

    std::string message = "WINNER: ";
    message += table->winner.getChar();
    showMessage(message);

}


//MULTI-PLAY
void multiPlay(){
    Player *player1 = new Player();
    Player *player2 = new Player();

    player1->setChar(inputChar("Player1: Set your pawn char:"));
    player2->setChar(inputChar("Player2: Set your pawn char:"));

    Table *table = new Table(*player1, *player2);
    table->print();

    while(!table->endGame) {
        player1->move(table);
        table->print();
        player2->move(table);
        table->print();
    }

    std::string message = "WINNER: ";
    message += table->winner.getChar();
    showMessage(message);

}
