#include <iostream>

// #include "./test/CriarCubo/CriarCubo.hpp"
#include "./test/CriarCurvaBezier/CriarCurvaBezier.hpp"

using namespace std;

int main()
{
    IDController *idController = new IDController();

    // criarCubo(idController);

    criarCurvaBezier(idController);

    return 0;
}