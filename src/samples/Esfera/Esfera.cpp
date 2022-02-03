#include "../samples.hpp"

Esfera::Esfera(int id) : Objeto(id)
{
}

Esfera::Esfera(int id, Ponto p0, Ponto centro, float r) : Objeto(id)
{
  this->p0 = p0;
  this->centro = centro;
  this->r = r;
}
bool Esfera::hitRay(VectorXd p0, VectorXd d, float &t_min, Eigen::Vector3d &n)
{
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

  // Salvando ponto de colisão com o raio
  Eigen::Vector3d p03d;
  p03d << p0.x(), p0.y(), p0.z();
  Eigen::Vector3d d3d;
  d3d << d.x(), d.y(), d.z();
  Eigen::Vector3d centro3d;
  centro3d << this->centro.x(), this->centro.y(), this->centro.z();

  Eigen::Vector3d colisedPoint = p03d + (t_min * d3d);
  n = (colisedPoint - centro3d) / this->r;

  return true;
}