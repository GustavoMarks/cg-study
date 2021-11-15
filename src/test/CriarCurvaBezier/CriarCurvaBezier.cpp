#include <iostream>

#include "CriarCurvaBezier.hpp"
#include "../../components/Objeto/Objeto.hpp"

void criarCurvaBezier(IDController *idController)
{
  Objeto jarro(idController->generateNewUID());

  Ponto p1{{1.0, 0.0, 0.0}};
  Ponto p2{{3.5, 0.5, 0.0}};
  Ponto p3{{0.0, 2.5, 0.0}};
  Ponto p4{{2.0, 3.0, 0.0}};

  jarro.criarCurvaBezier(p1, p2, p3, p4);
  

  std::cout << jarro;
}