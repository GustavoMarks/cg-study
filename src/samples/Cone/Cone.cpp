#include "../samples.hpp"

Cone::Cone(int id) : Objeto(id)
{
}

Cone::Cone(int id, VectorXd n, float h, float r, Ponto cb) : Objeto(id)
{
  this->id = id;
  n.normalize();
  this->n = n;
  this->h = h;
  this->r = r;
  this->cb = cb;
  this->V = cb + h * n;
}

bool Cone::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  VectorXd v = this->V - p0;

  float cos2theta = std::pow(this->h / std::sqrt(std::pow(this->h, 2) + std::pow(this->r, 2)), 2);
  float a = std::pow(d.dot(this->n), 2) - (d.dot(d) * cos2theta);
  float b = (v.dot(d) * cos2theta) - (v.dot(this->n) * d.dot(this->n));
  float c = std::pow(v.dot(this->n), 2) - (v.dot(v) * cos2theta);

  float delta = std::pow(b, 2) - a * c;
  if (delta < 0)
    return false;

  float t_int0 = (-1 * b + std::sqrt(delta)) / a;
  float t_int1 = (-1 * b - std::sqrt(delta)) / a;
  Ponto p1{{p0.x() + t_int0 * d.x(), p0.y() + t_int0 * d.y(), p0.z() + t_int0 * d.z()}};
  Ponto p2{{p0.x() + t_int1 * d.x(), p0.y() + t_int1 * d.y(), p0.z() + t_int1 * d.z()}};

  float p1_dotproduct = (this->V - p1).dot(this->n);
  float p2_dotproduct = (this->V - p2).dot(this->n);

  std::vector<float> intersecoes;

  if (t_int0 >= 0 && (0 <= p1_dotproduct && p1_dotproduct <= this->h))
    intersecoes.push_back(t_int0);
  if (t_int1 >= 0 && (0 <= p2_dotproduct && p2_dotproduct <= this->h))
    intersecoes.push_back(t_int1);

  if ((int)intersecoes.size() == 1)
  {
    Plano plano_base(0, this->cb, this->n); // TODO: ver questao do id
    float t_base;
    bool base_intersecao = plano_base.hitRay(p0, d, t_base);
    if (base_intersecao)
    {
      Ponto p_base{{p0.x() + t_base * d.x(), p0.y() + t_base * d.y(), p0.z() + t_base * d.z()}};
      VectorXd cbase = p_base - this->cb;
      if (t_base >= 0 && cbase.norm() < this->r)
        intersecoes.push_back(t_base);
    }
  }
  
  int num_intersecoes = (int)intersecoes.size();
  t_min = num_intersecoes > 0 ? intersecoes[0] : t_min;
  for (int i = 1; i < num_intersecoes; i++)
    if (intersecoes[i] < t_min)
      t_min = intersecoes[i];

  return num_intersecoes > 0;
}