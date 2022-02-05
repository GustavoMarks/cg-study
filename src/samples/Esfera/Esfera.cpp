#include "../samples.hpp"
#include <iostream>

Esfera::Esfera(int id) : Objeto(id)
{
}

Esfera::Esfera(int id, Ponto centro, float r) : Objeto(id)
{
  this->centro = centro;
  this->r = r;
}
bool Esfera::hitRay(VectorXd p0, VectorXd d, float &t_min, Eigen::Vector3d &n)
{
  VectorXd v = p0 - this->centro;
  float a = d.dot(d);
  float b = v.dot(d);
  float c = v.dot(v) - std::pow(this->r, 2);
  float delta = std::pow(b, 2) - (a * c);
  if (delta < 0)
    return false;
  float t1 = (std::sqrt(delta) - b) / a;
  float t2 = ((-std::sqrt(delta)) - b) / a;
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
  n.normalize();

  return true;
}