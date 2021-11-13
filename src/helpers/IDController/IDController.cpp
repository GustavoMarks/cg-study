#include "IDController.hpp"

IDController::IDController(){
    this->nextGlobalId = 0;
}

IDController::generateNewUID(){
    this->nextGlobalId = this->nextGlobalId + 1;
    return this->nextGlobalId;
}