#include "FileManager.h"

//CONSTRUCTOR
FileManager::FileManager(std::string fileName) {
    this->fileName = fileName + ".txt";
}

FileManager::~FileManager() = default;

/**
 * @name Save data
 * @brief Saves the pawns from the Table to the file
 * @param class Table
 *
 * This function simply saves the whole map of pawns line by line
 * in the .txt file with name provided in the CONSTRUCTOR.
 *
 */
void FileManager::save(Table *table) {
    auto pawns = table->getPawns();
    std::ofstream outputFile(fileName);

    //File error
    if (!outputFile) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    //File write
    for (const auto& pair : pawns) {
        const auto& position = pair.first;
        char pawn = pair.second;
        if (pawn == table->getPlayer1().getChar())
            outputFile << position[0] << ' ' << position[1] << ' ' << '1' << '\n';
        else if (pawn == table->getPlayer2().getChar())
            outputFile << position[0] << ' ' << position[1] << ' ' << '2' << '\n';
        else
            outputFile << position[0] << ' ' << position[1] << ' ' << pawn << '\n';
    }
    outputFile.close();

    table->print();
    std::cout << "Table saved to " << fileName << '\n';
}

/**
 * @name Load data
 * @brief Loads the pawns from the file to the Table
 * @param class Table
 *
 * This function if the exact opposite of the previous one.
 */
void FileManager::load(Table *table){
    std::map<std::array<int, 2>, char> pawns;
    std::ifstream inputFile(fileName);

    //File error
    if (!inputFile) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    int x, y;
    char c;
    //File read
    while (inputFile >> x >> y >> c) {
        if (c == '1')
            table->addPawn(x, y, table->getPlayer1().getChar());
        else if (c == '2')
            table->addPawn(x, y, table->getPlayer2().getChar());
        else
            table->addPawn(x, y, c);
    }
    inputFile.close();

    table->print();
    std::cout << "Table loaded from " << fileName << '\n';
}