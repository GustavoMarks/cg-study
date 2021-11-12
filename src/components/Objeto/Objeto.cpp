#include "Objeto.hpp"
#include <vector>

Objeto::Objeto(
    std::vector<Ponto> pontos,
    std::vector<Aresta> arestas,
    std::vector<Face> faces)
{
  this->pontos = pontos;
  this->arestas = arestas;
  this->faces = faces;
  // faltando id
}