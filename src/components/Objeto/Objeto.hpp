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
  void rotacionar(int plan, double ang);
  void rotacionar(Ponto P1, Ponto P2, double ang);
  void escalar(double sx, double sy, double sz);
  void cisalhar(double ang_onX_planXYZ);
  void refletir(int plan);
  void refletir(Ponto A, Ponto B, Ponto C);
  bool hitRay(); // TODO
};