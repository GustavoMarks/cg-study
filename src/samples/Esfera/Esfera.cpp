#include "../samples.hpp"
#include <iostream>

Esfera::Esfera(int id) : Objeto(id)
{
}

Esfera::Esfera(int id, Ponto centro, float r) : Objeto(id)
{
  std::vector<Ponto> pontos;
  pontos.push_back(centro);
  this->pontos = pontos;
  this->r = r;
}
bool Esfera::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  VectorXd v = p0 - this->pontos.at(0);
  float a = d.dot(d);
  float b = v.dot(d);
  float c = v.dot(v) - std::pow(this->r, 2);
  float delta = std::pow(b, 2) - (a * c);
  if (delta < 0)
    return false;
  float t1 = (std::sqrt(delta) - b) / a;
  float t2 = ((-std::sqrt(delta)) - b) / a;
  t_min = t1 < t2 ? t1 : t2;

  return true;
}

bool Esfera::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
  float t_min_light;
  bool resultHit = this->hitRay(p0Light, dLight, t_min_light);
  if (resultHit)
  {
    // Calculando ponto de interseção entre luz e objeto
    Eigen::VectorXd colisedPoint;
    colisedPoint = p0Light + (t_min_light * dLight);
    Eigen::VectorXd cpvXd{{colisedPointView.x(), colisedPointView.y(), colisedPointView.z()}};

    if (!colisedPoint.isApprox(cpvXd, 0.1))
    {
      return false;
    }

    // Buscando normal entre o ponto iluminado e a fonte de luz (esfera)
    Eigen::Vector3d p03d;
    p03d << p0Light.x(), p0Light.y(), p0Light.z();
    Eigen::Vector3d d3d;
    d3d << dLight.x(), dLight.y(), dLight.z();
    Eigen::Vector3d centro3d;
    centro3d << this->pontos.at(0).x(), this->pontos.at(0).y(), this->pontos.at(0).z();
    Eigen::Vector3d colised3d;
    colised3d << colisedPointView.x(), colisedPointView.y(), colisedPointView.z();

    n = (colised3d - centro3d) / this->r;
    n.normalize();

    return true;
  }

  return false;
}