#include <iostream>

#include "./test/CriarCurvaBezier/CriarCurvaBezier.hpp"
#include "./samples/Cubo/Cubo.hpp"

using namespace std;

int main()
{
    IDController *idController = new IDController();

    criarCurvaBezier(idController);
    
    // Criando um cubo com 3 de aresta
    Cubo *cubo = new Cubo(3.0, idController->generateNewUID());

    cout << "Criando um novo cubo de id: " << cubo->getId() << endl;

    return 0;
}