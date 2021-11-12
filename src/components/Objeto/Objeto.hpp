#include "../Ponto.hpp"
#include "../Aresta.hpp"
#include "../Face.hpp"
#include <vector>

class Objeto
{
private:
  static int id;
  std::vector<Ponto> pontos;
  std::vector<Aresta> arestas;
  std::vector<Face> faces;

public:
  Objeto(
      std::vector<Ponto> pontos,
      std::vector<Aresta> arestas,
      std::vector<Face> faces);
};