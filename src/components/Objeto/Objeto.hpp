#include "../Ponto.hpp"
#include "../Aresta.hpp"
#include "../Face.hpp"
#include <vector>

class Objeto
{
private:

public:
  int id;
  std::vector<Face> faces;
  
  Objeto(
      int id,
      std::vector<Face> faces);
  Objeto(int id);

  friend std::ostream& operator<<(std::ostream& os, Objeto& obj);

  int getId();
  void criarCurvaBezier(
      Ponto p0,
      Ponto p1,
      Ponto p2,
      Ponto p3);
};