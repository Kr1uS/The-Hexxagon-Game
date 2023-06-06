#include "Computer.h"
#include "Table.h"

Computer::Computer() = default;
Computer::~Computer() = default;

void Computer::move(Table *table) {
    Player::move(table);
}

/**
 * @name Get the Best position
 * @brief Algorithm finding the best solution
 * @param class Table
 * @return array with the best positions {x1, y1, x2, y2}
 *
 * This non-trivial function finds the best positions for
 * the move, which will lead to capturing the most of the opponent pawns.
 * It does so by creating a temporary local Table and iterating every
 * possible move on it in order to find the best one.
 */
std::array<int, 4> Computer::getPositions(Table *table) {
    std::array<int, 4> bestPositions;
    int maxCapturedPawns = 0;
    std::map<std::array<int, 2>, char> pawns = table->getPawns();

    // Iterate over all possible moves
    for (int x1 = 0; x1 < 17; x1++) {
        for (int y1 = 0; y1 < 4; y1++) {
            for (int x2 = 0; x2 < 17; x2++) {
                for (int y2 = 0; y2 < 4; y2++) {
                    // Check if the move is valid for the computer
                    if (table->isValidMove(x1, y1, x2, y2, *this)) {

                        // Simulate the move on a temporary table
                        Table tempTable = *table;

                        std::array<int, 4> positions = {x1, y1, x2, y2};
                        std::array<int, 2> from = {positions[0], positions[1]};
                        std::array<int, 2> to = {positions[2], positions[3]};

                        tempTable.addPawn(to[0], to[1], c);
                        std::map<std::array<int, 2>, char> tempPawns = tempTable.getPawns();

                        // Evaluate the move based on the captured pawns
                        int capturedPawns = 0;
                        for (const auto &pair : tempTable.getPawns()) {
                            int x = pair.first[0];
                            int y = pair.first[1];
                            char pawnC = pair.second;
                            if (tempTable.isAdjacent(x, y, to[0], to[1]) &&
                                pawnC != 'O' && pawnC != 'x' && pawnC != c) {
                                tempTable.addPawn(x, y, c);
                                capturedPawns++;
                            }
                        }

                        // Update the best positions if a better move is found
                        if (capturedPawns > maxCapturedPawns) {
                            bestPositions = positions;
                            maxCapturedPawns = capturedPawns;
                        }
                    }
                }
            }
        }
    }
    return bestPositions;
}


