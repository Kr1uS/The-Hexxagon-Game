#include "Player.h"
#include "Table.h"
#include "FileManager.h"

Player::Player() = default;
Player::~Player() = default;

char Player::getChar() const {
    return c;
}

void Player::setChar(char c) {
    this->c = c;
}

/**
 * @name Get valid positions
 * @brief Gets input from user for the positions
 * @param class Table
 * @return valid positions {x1, y1, x2, y2}
 *
 * This function returns array with four elements
 * x1 y1 for the initial position
 * x2 y2 for the final destination
 *
 * It will not stop until it will get input from the user,
 * which will be suitable for the function. Also it
 * contains functionality about saving and loading from file,
 * because user can save and load from any point of the game.
 *
 */
std::array<int, 4> Player::getPositions(Table *table) {
    int x1, x2, y1, y2;
    std::string s1, s2;

    auto isValidPosition = [&](int x, int y) {
        return table->isValidPosition(x, y, *this);
    };

    auto isValidMove = [&](int x1, int y1, int x2, int y2) {
        return table->isValidMove(x1, y1, x2, y2, *this);
    };

    auto handleInvalidInput = [&]() {
        table->print();
        std::cout << "\n!INVALID INPUT!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    };

    auto handleSaveLoadInput = [&](const std::string& action) {
        FileManager fileManager(s2);
        if (action == "save")
            fileManager.save(table);
        else if (action == "load")
            fileManager.load(table);
        else {
            table->print();
            std::cout << "\n!INVALID INPUT!\n";
            handleInvalidInput();
        }
    };

    while (true) {
        std::cout << c << " enter position from:\n>> ";
        std::cin >> s1 >> s2;
        try {
            x1 = std::stoi(s1);
            y1 = std::stoi(s2);

            if (isValidPosition(x1, y1)) {
                std::cout << '\n' << c << " enter position to:\n>> ";
                if (std::cin >> x2 >> y2 && isValidMove(x1, y1, x2, y2)) {
                    return {x1, y1, x2, y2};
                } else {
                    handleInvalidInput();
                }
            } else {
                handleInvalidInput();
            }
        } catch (const std::invalid_argument& e) {
            if (s1 == "save" || s1 == "load") {
                handleSaveLoadInput(s1);
            } else {
                handleInvalidInput();
            }
        }
    }
}

/**
 * @name Move
 * @brief Moves pawns on the Table
 * @param class Table
 *
 * This function gets positions from function Get valid positions
 * and adds the pawn on the Table. It also removes the pawn from
 * the Table if the move was 'jump' from cell to cell.
 */
void Player::move(Table *table) {
    std::array<int, 4> positions = getPositions(table);
    std::array<int, 2> from = {positions[0], positions[1]};
    std::array<int, 2> to = {positions[2], positions[3]};

    //ADD NEW PAWN
    table->addPawn(to[0], to[1], c);

    std::map<std::array<int, 2>, char> pawns = table->getPawns();

    //TAKE OPPONENTS ADJACENT PAWNS
    for (const auto &pair : table->getPawns()) {
        int x = pair.first[0];
        int y = pair.first[1];
        char pawnC = pair.second;
        if (table->isAdjacent(x, y, to[0], to[1]) &&
            pawnC != 'O' && pawnC != 'x' && pawnC != c) {
            table->addPawn(x, y, c);
        }
    }

    if (table->isFarAdjacent(from[0], from[1], to[0], to[1])) {
        table->removePawn(from[0], from[1]);
    }
}
