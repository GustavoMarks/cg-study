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
  void rotacionar(double aroundX_ang, double aroundY_ang, double aroundZ_ang);
  void escalar(double sx, double sy, double sz);
  bool hitRay(); // TODO
};