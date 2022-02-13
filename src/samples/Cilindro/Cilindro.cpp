#include "../samples.hpp"
#include <iostream>

using std::pow;
using std::sqrt;

Cilindro::Cilindro(int id) : Objeto(id)
{
}

Cilindro::Cilindro(int id, Ponto b, VectorXd u, float h, float r) : Objeto(id)
{
  // u é o vetor unitário que define a direção e o sentido do eixo do cilindro;
  std::vector<Ponto> pontos;
  // o centro da base do cilindro
  pontos.push_back(b);

  // Ponto do topo do cilindro;
  Ponto ct{{(u.x() * h) + b.x(), (u.y() * h) + b.y(), (u.z() * h) + b.z()}};
  pontos.push_back(ct);
  this->pontos = pontos;

  this->h = h;
  this->r = r;
}

bool Cilindro::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  int hitedSide = 0;
  return this->hitRayGetSide(p0, d, t_min, hitedSide);
}

bool Cilindro::hitRayGetSide(VectorXd p0, VectorXd d, float &t_min, int &hitedSide)
{
  VectorXd cilDir;
  cilDir = this->pontos.at(1) - this->pontos.at(0);
  cilDir.normalize();
  // Irá indicar o lado atingida primeiro com 1 (topo), 2 (base), 3 (lateral)
  bool hitBase = false;
  bool hitTop = false;
  bool hitSide = false;

  VectorXd v = (p0 - this->pontos.at(0)) - ((p0 - this->pontos.at(0)).dot(cilDir) * cilDir);
  VectorXd w = d - (d.dot(cilDir) * cilDir);

  float a = w.dot(w);
  float b = v.dot(w);
  float c = v.dot(v) - std::pow(this->r, 2);

  std::vector<float> intersecoes;

  if (a != 0)
  {
    float delta = std::pow(b, 2) - (a * c);
    if (delta < 0)
      return false;

    float t_int0 = (-1 * b + std::sqrt(delta)) / a;
    float t_int1 = (-1 * b - std::sqrt(delta)) / a;

    if (delta == 0)
    {
      t_min = t_int0 < t_int1 ? t_int0 : t_int1;
      hitedSide = 3;
      return true;
    }

    Ponto p1 = p0 + (t_int0 * d);
    Ponto p2 = p0 + (t_int1 * d);
    float p1_dotproduct = (p1 - this->pontos.at(0)).dot(cilDir);
    float p2_dotproduct = (p2 - this->pontos.at(0)).dot(cilDir);

    if (0 <= p1_dotproduct && p1_dotproduct <= this->h)
      intersecoes.push_back(t_int0);
    if (0 <= p2_dotproduct && p2_dotproduct <= this->h)
      intersecoes.push_back(t_int1);

    hitSide = true;
  }

  float t_base, t_topo;
  if ((int)intersecoes.size() < 2)
  {
    Ponto centro_topo{{
        this->pontos.at(0).x() + (this->h * cilDir.x()),
        this->pontos.at(0).y() + (this->h * cilDir.y()),
        this->pontos.at(0).z() + (this->h * cilDir.z()),
    }};
    Plano plano_base(0, this->pontos.at(0), cilDir * (-1));
    Plano plano_topo(1, centro_topo, cilDir);

    bool base_intersecao = plano_base.hitRay(p0, d, t_base);
    bool topo_intersecao = plano_topo.hitRay(p0, d, t_topo);

    if (base_intersecao)
    {
      Ponto p_base = p0 + (t_base * d);

      float distancia = sqrt(
          pow(this->pontos.at(0).x() - p_base.x(), 2) +
          pow(this->pontos.at(0).y() - p_base.y(), 2) +
          pow(this->pontos.at(0).z() - p_base.z(), 2));

      if (distancia <= this->r)
      {
        intersecoes.push_back(t_base);
        hitBase = true;
      }
    }

    if (topo_intersecao)
    {
      Ponto p_topo = p0 + (t_topo * d);

      float distancia = sqrt(
          pow(centro_topo.x() - p_topo.x(), 2) +
          pow(centro_topo.y() - p_topo.y(), 2) +
          pow(centro_topo.z() - p_topo.z(), 2));

      if (distancia <= this->r)
      {
        intersecoes.push_back(t_topo);
        hitTop = true;
      }
    }
  }

  int num_intersecoes = (int)intersecoes.size();
  t_min = num_intersecoes > 0 ? intersecoes[0] : t_min;
  for (int i = 1; i < num_intersecoes; i++)
    if (intersecoes[i] < t_min)
      t_min = intersecoes[i];

  if (hitTop && t_min == t_topo)
    hitedSide = 1;

  else if (hitBase && t_min == t_base)
    hitedSide = 2;

  else
    hitedSide = 3;

  return num_intersecoes > 0;
}

bool Cilindro::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
  VectorXd cilDir;
  cilDir = this->pontos.at(1) - this->pontos.at(0);
  cilDir.normalize();
  float t_min_light;
  int side = 0;
  bool resultHit = this->hitRayGetSide(p0Light, dLight, t_min_light, side);
  if (resultHit)
  {
    // Calculando ponto de interseção entre luz e objeto
    Eigen::VectorXd colisedPoint;
    colisedPoint = p0Light + (t_min_light * dLight);
    Eigen::VectorXd cpvXd{{colisedPointView.x(), colisedPointView.y(), colisedPointView.z()}};

    // std::cout << "atingiu" << std::endl;

    if (!colisedPoint.isApprox(cpvXd, 0.01))
    {
      // std::cout << "não é proximo" << std::endl;
      return false;
    }

    // Calculando vetor normal
    if (side == 1)
    {
      // Topo
      n << cilDir.x(), cilDir.y(), cilDir.z();
    }
    if (side == 2)
    {
      // Base
      n << (-1) * cilDir.x(), (-1) * cilDir.y(), (-1) * cilDir.z();
    }
    if (side == 3)
    {
      // Lateral
      // Salvando ponto de colisão com o raio
      Eigen::Vector3d p03d;
      p03d << p0Light.x(), p0Light.y(), p0Light.z();
      Eigen::Vector3d d3d;
      d3d << dLight.x(), dLight.y(), dLight.z();
      Eigen::Vector3d cb3d;
      cb3d << this->pontos.at(0).x(), this->pontos.at(0).y(), this->pontos.at(0).z();
      Eigen::Vector3d dc3d;
      dc3d << cilDir.x(), cilDir.y(), cilDir.z();

      Eigen::Vector3d colisedPoint3d = p03d + (t_min_light * d3d);

      Eigen::Vector3d N = (colisedPoint3d - cb3d) - ((colisedPoint3d - cb3d).dot(dc3d) * dc3d);
      N.normalize();
      n = N / this->r;
    }

    n.normalize();

    return true;
  }

  return false;
}