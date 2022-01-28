#include "../samples.hpp"

Cilindro::Cilindro(int id) : Objeto(id)
{
}

Cilindro::Cilindro(int id, Ponto b, VectorXd u, float h, float r) : Objeto(id)
{
  this->id = id;
  this->b = b;
  this->u = u;
  this->h = h;
  this->r = r;
}

bool Cilindro::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
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
      VectorXd cbase = p_base - this->b;
      if (t_base >= 0 && cbase.norm() < this->r)
        intersecoes.push_back(t_base);
    }
    if (topo_intersecao)
    {
      Ponto p_base{{p0.x() + t_topo * d.x(), p0.y() + t_topo * d.y(), p0.z() + t_topo * d.z()}};
      VectorXd ctopo = p_base - this->b;
      if (t_topo >= 0 && ctopo.norm() < this->r)
        intersecoes.push_back(t_topo);
    }
  }

  int num_intersecoes = (int)intersecoes.size();
  t_min = num_intersecoes > 0 ? intersecoes[0] : t_min;
  for (int i = 1; i < num_intersecoes; i++)
    if (intersecoes[i] < t_min)
      t_min = intersecoes[i];

  return num_intersecoes > 0;
}