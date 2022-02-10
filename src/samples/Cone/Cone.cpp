#include "../samples.hpp"
#include <iostream>
#include <math.h>

Cone::Cone(int id) : Objeto(id)
{
}

Cone::Cone(int id, VectorXd n, float h, float r, Ponto cb) : Objeto(id)
{
  std::vector<Ponto> pontos;
  // Ponto central da base
  pontos.push_back(cb);
  this->pontos = pontos;

  n.normalize();
  this->n = n;
  this->h = h;
  this->r = r;
}

bool Cone::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  int hitedSide = 0;
  return this->hitRayGetSide(p0, d, t_min, hitedSide);
}

bool Cone::hitRayGetSide(VectorXd p0, VectorXd d, float &t_min, int &hitedSide)
{
  // hitedSide indica onde o cone foi atingido, 1 para lateral, 2 para base
  hitedSide = 1;
  Ponto vertice = this->pontos.at(0) + (this->h * this->n);
  VectorXd v = vertice - p0;

  float cos2theta = std::pow(this->h / std::sqrt(std::pow(this->h, 2) + std::pow(this->r, 2)), 2);
  float a = std::pow(d.dot(this->n), 2) - (d.dot(d) * cos2theta);
  float b = (v.dot(d) * cos2theta) - (v.dot(this->n) * d.dot(this->n));
  float c = std::pow(v.dot(this->n), 2) - (v.dot(v) * cos2theta);

  float delta = std::pow(b, 2) - a * c;
  if (delta < 0)
    return false;

  float t_int0;
  float t_int1;

  if (a == 0)
  {
    // Raio é paralelo a alguma geratriz do cone
    t_int0 = (-1) * (c / (2 * b));
    t_int1 = t_int0;
  }
  else
  {
    t_int0 = (-1 * b + std::sqrt(delta)) / a;
    t_int1 = (-1 * b - std::sqrt(delta)) / a;
  }

  Ponto p1{{p0.x() + t_int0 * d.x(), p0.y() + t_int0 * d.y(), p0.z() + t_int0 * d.z()}};
  Ponto p2{{p0.x() + t_int1 * d.x(), p0.y() + t_int1 * d.y(), p0.z() + t_int1 * d.z()}};

  float p1_dotproduct = (vertice - p1).dot(this->n);
  float p2_dotproduct = (vertice - p2).dot(this->n);

  std::vector<float> intersecoes;

  if (t_int0 >= 0 && (0 <= p1_dotproduct && p1_dotproduct <= this->h))
    intersecoes.push_back(t_int0);
  if (t_int1 >= 0 && (0 <= p2_dotproduct && p2_dotproduct <= this->h))
    intersecoes.push_back(t_int1);

  if ((int)intersecoes.size() == 1)
  {
    Plano plano_base(0, this->pontos.at(0), this->n * (-1));
    float t_base;
    bool base_intersecao = plano_base.hitRay(p0, d, t_base);
    if (base_intersecao)
    {
      // Buscando ponto de interseção entre plano da base e raio
      Eigen::VectorXd colisedPoint;
      colisedPoint = p0 + (t_base * d);

      // Calculando distância entre ponto de colisão e centro da base
      Ponto centroBase = this->pontos.at(0);
      float distancia = std::sqrt(
          std::pow(colisedPoint.x() - centroBase.x(), 2) +
          std::pow(colisedPoint.y() - centroBase.y(), 2) +
          std::pow(colisedPoint.z() - centroBase.z(), 2));

      if (distancia <= this->r)
        intersecoes.push_back(t_base);

      if (t_base < intersecoes.at(0))
        hitedSide = 2;
    }
  }

  int num_intersecoes = (int)intersecoes.size();
  t_min = num_intersecoes > 0 ? intersecoes[0] : t_min;
  for (int i = 1; i < num_intersecoes; i++)
    if (intersecoes[i] < t_min)
      t_min = intersecoes[i];

  return num_intersecoes > 0;
}

bool Cone::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
  float t_min_light;
  int side = 0;
  bool resultHit = this->hitRayGetSide(p0Light, dLight, t_min_light, side);
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

    // Calculando vetor normal
    if (side == 2)
    {
      // Base
      n << (-1) * this->n.x(), (-1) * this->n.y(), (-1) * this->n.z();
    }
    if (side == 1)
    {
      // Lateral
      Ponto vertice = this->pontos.at(0) + (this->h * this->n);
      Eigen::Vector3d vertice3d;
      vertice3d << vertice.x(), vertice.y(), vertice.z();
      Eigen::Vector3d p03d;
      p03d << p0Light.x(), p0Light.y(), p0Light.z();
      Eigen::Vector3d d3d;
      d3d << dLight.x(), dLight.y(), dLight.z();
      Eigen::Vector3d cb3d;
      cb3d << this->pontos.at(0).x(), this->pontos.at(0).y(), this->pontos.at(0).z();
      Eigen::Vector3d dc3d;
      dc3d << this->n.x(), this->n.y(), this->n.z();

      Eigen::Vector3d colisedPoint = p03d + (t_min_light * d3d);

      Eigen::Vector3d W;

      W = colisedPoint - cb3d;
      W = dc3d.cross(W);
      n = vertice3d - colisedPoint;
      n = W.cross(n);
    }

    n.normalize();

    return true;
  }

  return false;
}