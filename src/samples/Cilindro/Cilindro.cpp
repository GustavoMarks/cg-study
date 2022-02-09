#include "../samples.hpp"
#include <iostream>

using std::pow;
using std::sqrt;

Cilindro::Cilindro(int id) : Objeto(id)
{
}

Cilindro::Cilindro(int id, Ponto b, VectorXd u, float h, float r) : Objeto(id)
{
  this->id = id;
  this->b = b;
  u.normalize();
  this->u = u;
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

  // TODO: Verificando se vetor d é paralelo ao vetor do cilindro

  // Irá indicar o lado atingida primeiro com 1 (topo), 2 (base), 3 (lateral)
  VectorXd v = (p0 - this->b) - ((p0 - this->b).dot(this->u) * u);
  VectorXd w = d - (d.dot(this->u) * u);

  float a = w.dot(w);
  float b = v.dot(w);
  float c = v.dot(v) - std::pow(this->r, 2);

  float delta = std::pow(b, 2) - a * c;
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

  Ponto p1{{p0.x() + t_int0 * d.x(), p0.y() + t_int0 * d.y(), p0.z() + t_int0 * d.z()}};
  Ponto p2{{p0.x() + t_int1 * d.x(), p0.y() + t_int1 * d.y(), p0.z() + t_int1 * d.z()}};
  float p1_dotproduct = (p1 - this->b).dot(this->u);
  float p2_dotproduct = (p2 - this->b).dot(this->u);

  std::vector<float> intersecoes;

  if (t_int0 >= 0 && (0 <= p1_dotproduct && p1_dotproduct <= this->h))
    intersecoes.push_back(t_int0);
  if (t_int1 >= 0 && (0 <= p2_dotproduct && p2_dotproduct <= this->h))
    intersecoes.push_back(t_int1);

  if ((int)intersecoes.size() < 2)
  {
    Ponto centro_topo{{this->u.x() * this->h, this->u.y() * this->h, this->u.z() * this->h}};
    Plano plano_base(0, this->b, this->u);     // TODO: ver questao do id
    Plano plano_topo(1, centro_topo, this->u); // TODO: ver questao do id
    float t_base, t_topo;
    bool base_intersecao = plano_base.hitRay(p0, d, t_base);
    bool topo_intersecao = plano_topo.hitRay(p0, d, t_topo);

    if (base_intersecao)
    {
      Ponto p_base{{p0.x() + t_base * d.x(), p0.y() + t_base * d.y(), p0.z() + t_base * d.z()}};
      // VectorXd cbase = p_base - this->b;
      float distancia = sqrt(pow(this->b.x() - p_base.x(), 2) + pow(this->b.y() - p_base.y(), 2) + pow(this->b.z() - p_base.z(), 2));
      // if (t_base >= 0 && cbase.norm() < this->r)
      if (distancia < this->r)
        intersecoes.push_back(t_base);

      if (topo_intersecao && t_topo < t_base)
        hitedSide = 1;
      else if (intersecoes.size() >= 1 && intersecoes.at(0) < t_base)
        hitedSide = 3;
      else
        hitedSide = 2;
    }
    if (topo_intersecao)
    {
      Ponto p_topo{{p0.x() + t_topo * d.x(), p0.y() + t_topo * d.y(), p0.z() + t_topo * d.z()}};
      // VectorXd ctopo = p_topo - this->b;
      VectorXd ctopo = this->b * this->h;
      float distancia = sqrt(pow(ctopo.x() - p_topo.x(), 2) + pow(ctopo.y() - p_topo.y(), 2) + pow(ctopo.z() - p_topo.z(), 2));
      // if (t_topo >= 0 && ctopo.norm() < this->r)
      if (distancia < this->r)
        intersecoes.push_back(t_topo);

      if (base_intersecao && t_topo > t_base)
        hitedSide = 2;
      else if (intersecoes.size() >= 1 && intersecoes.at(0) < t_base)
        hitedSide = 3;
      else
        hitedSide = 1;
    }
  }
  else if ((int)intersecoes.size() == 2)
  {
    hitedSide = 3;
  }

  int num_intersecoes = (int)intersecoes.size();
  t_min = num_intersecoes > 0 ? intersecoes[0] : t_min;
  for (int i = 1; i < num_intersecoes; i++)
    if (intersecoes[i] < t_min)
      t_min = intersecoes[i];

  return num_intersecoes > 0;
}

bool Cilindro::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
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
    if (side == 1)
    {
      n << this->u.x(), this->u.y(), this->u.z();
    }
    if (side == 2)
    {
      n << (-1) * this->u.x(), (-1) * this->u.y(), (-1) * this->u.z();
    }
    if (side == 3)
    {
      // Salvando ponto de colisão com o raio
      Eigen::Vector3d p03d;
      p03d << p0Light.x(), p0Light.y(), p0Light.z();
      Eigen::Vector3d d3d;
      d3d << dLight.x(), dLight.y(), dLight.z();
      Eigen::Vector3d cb3d;
      cb3d << this->b.x(), this->b.y(), this->b.z();
      Eigen::Vector3d dc3d;
      dc3d << this->u.x(), this->u.y(), this->u.z();

      Eigen::Vector3d colisedPoint3d = p03d + (t_min_light * d3d);

      Eigen::Vector3d N = (colisedPoint3d - cb3d) - ((colisedPoint3d - cb3d).dot(d3d) * d3d);
      n = N / this->r;
      n.normalize();
    }

    return true;
  }

  return false;
}