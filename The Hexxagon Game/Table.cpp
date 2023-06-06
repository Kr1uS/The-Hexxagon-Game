#include "Table.h"
#include "Player.h"

/**
 * @name CONSTRUCTOR
 * @brief Constructs the Table
 * @param class Player for player1
 * @param class Player for player2
 *
 * This constructor sets the initial positions for characters
 * and players pawns. It also has commented section for testing
 * the endGame and Winner functionality.
 */
Table::Table(Player player1, Player player2) {
    this->player1 = player1;
    this->player2 = player2;

    //Adding chars to the Table
    this->table.push_back(std::vector<char>{'O'});
    this->table.push_back(std::vector<char>{'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'x', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'x', 'x', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O', 'O'});
    this->table.push_back(std::vector<char>{'O', 'O'});
    this->table.push_back(std::vector<char>{'O'});

    //Initialising positions
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            pawns[{i, j}] = table[i][j];
        }
    }
    pawns[{0, 0}] = player2.getChar();
    pawns[{12, 0}] = player2.getChar();
    pawns[{12, 4}] = player2.getChar();
    pawns[{16, 0}] = player1.getChar();
    pawns[{4, 0}] = player1.getChar();
    pawns[{4, 4}] = player1.getChar();

//    //TEST FOR WINNER 2
//    for (int i = 0; i < 17; i++) {
//        pawns[{i, 0}] = player2.getChar();
//    }
//    for (int i = 1; i < 16; i++) {
//        pawns[{i, 1}] = player2.getChar();
//    }
//    for (int i = 2; i < 15; i++) {
//        pawns[{i, 2}] = player2.getChar();
//    }
//    for (int i = 3; i < 14; i++) {
//        pawns[{i, 3}] = player2.getChar();
//    }

}

Table::~Table() = default;

/**
 * @name Update
 * @brief Updates the Table data
 *
 * This update function sets the needed characters to the
 * table vector of characters in order to initialise it with
 * map of pawns.
 */
void Table::update(){
    //COUNT PAWNS
    this->pawns1 = 0;
    this->pawns2 = 0;
    //DISPLAY PAWNS
    for (const auto &pair : pawns) {
        int x = pair.first[0];
        int y = pair.first[1];
        char pawn = pair.second;
        table[x][y] = pawn;
        if (pawn == player1.getChar()) this->pawns1++;
        if (pawn == player2.getChar()) this->pawns2++;
    }
    checkEndGame();
}

/**
 * @name Check End Game
 * @brief Checks the Table for the end of the game
 *
 * This checking function changes value of bool variable endGame and
 * defines variable winner with the one of the players who won.
 */
void Table::checkEndGame() {
    //COUNT MOVES
    int moves1 = 0;
    int moves2 = 0;
    //CHECK MOVES
    for (const auto &pair1 : pawns) {
        int x1 = pair1.first[0];
        int y1 = pair1.first[1];
        for (const auto &pair2 : pawns) {
            int x2 = pair2.first[0];
            int y2 = pair2.first[1];
            if (isValidMove(x1, y1, x2, y2, player1)) moves1++;
            if (isValidMove(x1, y1, x2, y2, player2)) moves2++;
        }
    }
    if (moves1 == 0) {
        this->winner = player2;
        endGame = true;
    }
    if (moves2 == 0) {
        this->winner = player1;
        endGame = true;
    }

    //COUNT EMPTY SPACES
    int empty = 0;
    for (const auto &pair : pawns) {
        if (pair.second == 'O') empty++;
    }
    if (empty == 0) {
        if (pawns1 > pawns2) {
            this->winner = player1;
            endGame = true;
        }
        if (pawns1 < pawns2) {
            this->winner = player2;
            endGame = true;
        }
        if (pawns1 == pawns2) {
            Player *nobody = new Player();
            nobody->setChar('&');
            this->winner = *nobody;
            endGame = true;
        }
    }
}

void Table::print() {
    update();
    for (const std::vector<char> vector : this->table) {
        for (int i = 0; i < 5 - vector.size(); i++) std::cout << " \t";
        for (const char c : vector) {
            std::cout << c << "\t \t";
        }
        std::cout << '\n';
    }
    std::cout << player1.getChar() << ": " << pawns1 << '\n';
    std::cout << player2.getChar() << ": " << pawns2 << '\n';
}

std::map<std::array<int, 2>, char> Table::getPawns() {
    return this->pawns;
}

void Table::addPawn(int x, int y, char c) {
    pawns[{x, y}] = c;
}

void Table::removePawn(int x, int y) {
    pawns[{x, y}] = 'O';
}

bool Table::isAdjacent(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    return (dx == 1 && dy == 0) || (dx == 1 && dy == 1) || (dx==0 && dy ==1);
}

bool Table::isFarAdjacent(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    return (dx == 2 && dy == 1) || (dx == 2 && dy == 2) || (dx == 1 && dy == 2);
}

/**
 * @name Is Move Valid?
 * @brief Checks if the provided move is valid
 * @param x1, y1, x2, y2, class Player
 * @return bool value
 *
 * This function passes the arguments through the list of 5 Rules
 * and returns True if the move is valid and False otherwise.
 */
bool Table::isValidMove(int x1, int y1, int x2, int y2, Player player) {
    // Rule 1: Check if initial position is within the boundaries
    if (x1 < 0 || x1 >= table.size() || y1 < 0 || y1 >= table[x1].size()) {
        return false;
    }

    // Rule 2: Check if desired position is within the boundaries
    if (x2 < 0 || x2 >= table.size() || y2 < 0 || y2 >= table[x2].size()) {
        return false;
    }

    // Rule 3: Check if initial position contains player's pawn
    if (table[x1][y1] != player.getChar()) {
        return false;
    }

    // Rule 4: Check if desired position is empty
    if (table[x2][y2] != 'O') {
        return false;
    }

    // Rule 5: Check if desired position is adjacent to the initial position
    if (!isAdjacent(x1, y1, x2, y2) && !isFarAdjacent(x1, y1, x2, y2)) {
        return false;
    }

    // All rules passed, move is valid
    return true;
}

/**
 * @name Is the position valid?
 * @brief Checks if the position is valid
 * @param x, y, class Player
 * @return bool value
 *
 * This function checks if the Player has a permission to move the
 * pawn located on x y on the Table and return True if he does and
 * False otherwise.
 */
bool Table::isValidPosition(int x, int y, Player player) {
    std::array<int, 2> position = {x, y};

    auto it = pawns.find(position);
    if (it != pawns.end() && it->second == player.getChar()) {
        //Pawn exists at the given position and has the same character as player
        return true;
    }

    //No pawn at the given position or the character doesn't match
    return false;
}

Player Table::getPlayer1() {
    return player1;
}

Player Table::getPlayer2() {
    return player2;
}
