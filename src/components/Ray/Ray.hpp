#include "../Ponto.hpp"
#include "../Cenario/Cenario.hpp"

class Ray
{
public:
  Ponto Eye;
  Ponto plc;
  Ray(Ponto Eye, Ponto plc);
  bool computarIntersecao(Cenario cenario);
};
