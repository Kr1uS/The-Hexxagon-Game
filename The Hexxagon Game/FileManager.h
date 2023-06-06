#ifndef THE_HEXXAGON_GAME_FILEMANAGER_H
#define THE_HEXXAGON_GAME_FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <map>
#include "Table.h"
#include "Player.h"

class FileManager {
private:
    std::string fileName;
public:
    //CONSTRUCTOR
    FileManager(std::string fileName);
    //DESTRUCTOR
    virtual ~FileManager();

    //FUNCTIONS
    void save(Table *table);
    void load(Table *table);

};


#endif //THE_HEXXAGON_GAME_FILEMANAGER_H
