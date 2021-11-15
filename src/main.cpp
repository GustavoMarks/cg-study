#include <iostream>

#include "./test/CriarCubo/CriarCubo.hpp"

using namespace std;

int main() {
    IDController *idController = new IDController();

    criarCubo(idController);

    return 0;
}