#include "../Ponto.hpp"
#include "../Aresta.hpp"
#include "../Face.hpp"
#include <vector>

class Objeto
{
private:
  std::vector<Face> faces;

public:
  static int id;
  Objeto(
      int id,
      std::vector<Face> faces);
  
  int getId();
};