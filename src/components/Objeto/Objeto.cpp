#include <iostream>
#include <eigen-3.4.0/Eigen/Dense>
#include "Objeto.hpp"

#define PI 3.14159265

using namespace std;

Objeto::Objeto(int id)
{
  this->id = id;
}

Objeto::Objeto(int id, std::vector<Ponto> pontos)
{
  this->pontos = pontos;
  this->id = id;
}

void Objeto::transladar(Ponto t)
{
  // construindo matriz de translacao
  Eigen::MatrixXd m = Eigen::Matrix4d::Identity(4, 4);
  m(0, 3) = t.x();
  m(1, 3) = t.y();
  m(2, 3) = t.z();

  // gerando os novos vertices
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector4d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z(), 1;

    v = m * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

bool Objeto::hitRay(){
  return false;
}