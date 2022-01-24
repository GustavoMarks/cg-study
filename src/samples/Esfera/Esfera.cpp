#include "../samples.hpp"

Esfera::Esfera()
{
}

Esfera::Esfera(Ponto p0, Ponto centro, float r)
{
  this->p0 = p0;
  this->centro = centro;
  this->r = r;
}
bool Esfera::hitRay(Ray raio, float& t_min)
{
  VectorXd p0 = raio.p0;
  VectorXd d = raio.d;

  VectorXd v = p0 - d;
  float a = d.dot(d);
  float b = v.dot(d);
  float c = v.dot(v) - std::pow(this->r, 2);
  float delta = 4 * std::pow(b, 2) - 4 * a * c;
  if (delta < 0)
    return false;
  float t1 = (-2 * b + std::sqrt(delta)) / (2 * a);
  float t2 = (-2 * b - std::sqrt(delta)) / (2 * a);
  t_min = t1 < t2 ? t1 : t2;
  return true;
}