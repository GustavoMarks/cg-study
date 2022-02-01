#include "Ray.hpp"
#include <iostream>

Ray::Ray(Ponto p0, Ponto d)
{
  this->p0 = p0;
  d.normalize();
  this->d = d;
}

bool Ray::computarIntersecao(Cenario cenario)
{
  vector<Objeto*> objs = cenario.objs;
  int i;
  float t_min = 0;
  float aux = 0;
  bool finalResult = false;
  bool iResult = false;
  for (i = 0; i < objs.size(); i++)
  {
    aux = t_min;
    iResult = objs.at(i)->hitRay(this->p0, this->d, t_min);
    if (iResult)
    {
      t_min = aux < t_min ? aux : t_min;
      finalResult = iResult;
    }
  }

  return finalResult;
}