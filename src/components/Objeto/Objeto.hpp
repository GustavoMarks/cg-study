#include "../Ponto.hpp"
#include "../Aresta.hpp"
#include "../Face.hpp"
#include <vector>

class Objeto
{
private:
  std::vector<Face> faces;

public:
  int id;
  Objeto(
      int id,
      std::vector<Face> faces);

  int getId();
  void criarCurvaBezier(
      Ponto p0,
      Ponto p1,
      Ponto p2,
      Ponto p3);
};