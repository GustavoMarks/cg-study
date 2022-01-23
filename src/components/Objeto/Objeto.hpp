#include "../Ponto.hpp"
#include <vector>

class Objeto
{
private:

public:
  int id;
  std::vector<Ponto> pontos;

  Objeto(int id);
  Objeto(int id, std::vector<Ponto> pontos);

  void transladar(Ponto t);
  bool hitRay(); // TODO
};