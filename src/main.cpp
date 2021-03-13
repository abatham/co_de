#include <iostream>

#include "mongocxx/instance.hpp"

#include "mongodb_handler.h"

void printRes(bool res, const std::string& operationType){
    std::cout << operationType << " " << (res? "succeeded.": "failed.") << std::endl;
}

int main() {
    mongocxx::instance instance ;
    local::MongoDbHandler dbHandler;

    // dbHandler.AddCharacterToDB("Luigi", /*local::CharacterSize::kLarge*/ "medium", 2);
    // dbHandler.UpdateWins("604cbedd391a655464184cf2");
    // dbHandler.UpdateWins("604cd0701555d8592c454ad2");
    // dbHandler.RemoveCharacterFromDB("604cd0d6e87256626f518b42");

    printRes(dbHandler.AddCharacterToDB("Luigi", /*local::CharacterSize::kLarge*/ "medium", 2), "Insert");
    printRes(dbHandler.UpdateWins("604cbedd391a655464184cf2"), "Update");
    printRes(dbHandler.UpdateWins("604cd0701555d8592c454ad2"), "Update");
    printRes(dbHandler.RemoveCharacterFromDB("604cd47f955213750b116bb2"), "Delete");
    printRes(dbHandler.RemoveCharacterFromDB("604cd4811549721f745431c2"), "Delete");
}