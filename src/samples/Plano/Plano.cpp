#include "../samples.hpp"

Plano::Plano(int id) : Objeto(id)
{
}

Plano::Plano(int id, Ponto p0, VectorXd n) : Objeto(id)
{
  this->p0 = p0;
  this->n = n;
}

bool Plano::hitRay(VectorXd p0, VectorXd d, float &t_int)
{
  if(d.dot(this->n) == 0)
    return false;
  VectorXd resultante = this->p0 - p0;
  t_int = resultante.dot(this->n) / d.dot(this->n);
  return true;
}