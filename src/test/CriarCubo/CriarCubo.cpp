#include <iostream>
#include "CriarCubo.hpp"
#include "../../components/Objeto/Objeto.hpp"

using namespace std;

void criarCubo(IDController *idController)
{
  
  // Gerando um cubo 3x3x3
  Ponto p1{{0, 0, 0}};
  Ponto p2{{3.0, 0, 0}};
  Ponto p3{{3.0, 0, 3.0}};
  Ponto p4{{0, 0, 3.0}};
  Ponto p5{{0, 3.0, 0}};
  Ponto p6{{3.0, 3.0, 0}};
  Ponto p7{{3.0, 3.0, 3.0}};
  Ponto p8{{0, 3.0, 3.0}};

  Aresta a1 = make_pair(p1, p5);
  Aresta a2 = make_pair(p5, p2);
  Aresta a3 = make_pair(p2, p1);
  Aresta a4 = make_pair(p5, p6);
  Aresta a5 = make_pair(p6, p2);

  Aresta a6 = make_pair(p1, p4);
  Aresta a7 = make_pair(p4, p8);
  Aresta a8 = make_pair(p8, p1);
  Aresta a9 = make_pair(p8, p5);

  Aresta a10 = make_pair(p8, p7);
  Aresta a11 = make_pair(p7, p5);
  Aresta a12 = make_pair(p7, p6);

  Aresta a13 = make_pair(p7, p3);
  Aresta a14 = make_pair(p3, p6);

  Aresta a15 = make_pair(p3, p2);
  Aresta a16 = make_pair(p2, p4);
  Aresta a17 = make_pair(p4, p3);

  Aresta a18 = make_pair(p4, p7);

  // Faces frontais
  Face f1 = make_tuple(a18, a10, a7);
  Face f2 = make_tuple(a17, a13, a18);

  // Faces direitas
  Face f3 = make_tuple(a13, a14, a12);
  Face f4 = make_tuple(a15, a5, a14);

  // Faces do fundo
  Face f5 = make_tuple(a3, a1, a2);
  Face f6 = make_tuple(a2, a4, a5);

  // Faces da esquerda
  Face f7 = make_tuple(a1, a8, a9);
  Face f8 = make_tuple(a8, a7, a8);

  // Faces do topo
  Face f9 = make_tuple(a10, a11, a9);
  Face f10 = make_tuple(a11, a12, a4);

  // Faces de baixo
  Face f11 = make_tuple(a17, a16, a15);
  Face f12 = make_tuple(a16, a6, a3);

  Objeto *cubo3d = new Objeto(idController->generateNewUID(), {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12});

  cout << "Cubo criado, id: " << cubo3d->getId() << endl;
}