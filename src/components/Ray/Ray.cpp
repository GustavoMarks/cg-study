#include "Ray.hpp"

Ray::Ray(Ponto Eye, Ponto plc)
{
  this->Eye = Eye;
  this->plc = plc;
}

bool Ray::computarIntersecao(Cenario *cenario)
{
}