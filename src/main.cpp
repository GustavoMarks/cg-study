#include <iostream>

#include "./samples/samples.hpp"
#include "./helpers/IDController/IDController.hpp"
#include "./helpers/Window/Window.hpp"

using namespace std;

int main(int argc, char **argv)
{
    IDController *idController = new IDController();

    // Criando um cubo com 3 de aresta
    Cubo *cubo = new Cubo(3.0, idController->generateNewUID());
    cout << "Criado novo cubo de id: " << cubo->id << endl;

    // Criando jarro com 6 meridianos e 6 paralelos
    Ponto p1{{1.0, 0.0, 0.0}};
    Ponto p2{{3.5, 0.5, 0.0}};
    Ponto p3{{0.0, 2.5, 0.0}};
    Ponto p4{{2.0, 3.0, 1.0}};
    CurvaBezier *jarro = new CurvaBezier(6, 6, p1, p2, p3, p4, idController->generateNewUID());

    cout << "Criado novo jarro de id: " << jarro->id << endl;

    jarro->transladar(p4);
    jarro->rotacionar(45, 0, 0);
    jarro->escalar(2, 2, 2);

    // Abrindo uma janela com Open GL
    Window w(argc, argv, 800, 600, "CG Study");

    return 0;
}