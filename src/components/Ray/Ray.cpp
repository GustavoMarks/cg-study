#include "Ray.hpp"

Ray::Ray(Ponto p0, Ponto d)
{
  this->p0 = p0;
  d.normalize();
  this->d = d;
}

bool Ray::computarIntersecao(Cenario cenario)
{
  return true;
}