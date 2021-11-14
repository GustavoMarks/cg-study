#include "IDController.hpp"

using namespace std;

IDController::IDController(){
    this->nextGlobalId = 0;
}

int IDController::generateNewUID(){
    this->nextGlobalId = this->nextGlobalId + 1;
    return this->nextGlobalId;
}