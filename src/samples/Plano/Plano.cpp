#include "../samples.hpp"
#include <vector>
#include <iostream>

Plano::Plano(int id) : Objeto(id)
{
}

Plano::Plano(int id, Ponto p0, VectorXd n) : Objeto(id)
{
  std::vector<Ponto> pontos;
  // um ponto específico (conhecido) do plano;
  pontos.push_back(p0);
  this->pontos = pontos;

  n.normalize();
  this->n = n;
}

bool Plano::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  if (!(this->n.dot(d * (-1)) >= 0 && this->n.dot(d * (-1)) <= 1))
    return false;
  VectorXd resultante = this->pontos.at(0) - p0;
  t_min = resultante.dot(this->n) / d.dot(this->n);
  return true;
}

bool Plano::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
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

    n << this->n.x(), this->n.y(), this->n.z();

    return true;
  } else {
    // std::cout << "não atingiu" << std::endl;

  }

  return false;
}