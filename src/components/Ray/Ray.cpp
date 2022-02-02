#include "Ray.hpp"
#include <iostream>

using namespace std;

Ray::Ray(Ponto p0, Ponto d)
{
  this->p0 = p0;
  d.normalize();
  this->d = d;
}

bool Ray::computarIntersecao(Cenario cenario, RGBIntesity &I)
{
  vector<Objeto *> objs = cenario.objs;
  float t_min = 0;
  float aux = 0;
  bool finalResult = false;
  bool iResult = false;
  int objPosition = 0;
  for (int i = 0; i < objs.size(); i++)
  {
    aux = t_min;
    iResult = objs.at(i)->hitRay(this->p0, this->d, t_min);
    if (iResult)
    {
      if (aux < t_min)
      {
        t_min = aux;
      }
      else
      {
        objPosition = i;
      }
      finalResult = iResult;
    }
  }

  // Calculando luminosidade
  vector<LuzAmbiente *> luzes = cenario.luzes;
  for (int i = 0; i < luzes.size(); i++)
  {
    LuzAmbiente *luzAtual = luzes.at(i);
    Objeto *finded = objs.at(objPosition);

    // Luminosidade ambiete
    RGBIntesity Ia = luzAtual->i;
    I = I.sum(finded->ka.cross(Ia));

    // TODO: Calcular luminosidade difusa e especular
  }

  return finalResult;
}