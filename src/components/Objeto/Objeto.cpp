#include <iostream>
#include <eigen-3.4.0/Eigen/Dense>
#include <math.h>
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

void Objeto::rotacionar(double aroundX_ang, double aroundY_ang, double aroundZ_ang)
{
  // Matriz para rotação em torno do eixo X
  // OBS.: Entrada das funções é em radianos, fazendo conversão dos parâmentros
  Eigen::Matrix3d mAroundX;
  mAroundX << 1, 0, 0,
      0, cos(aroundX_ang * PI / 180.0), (-1) * sin(aroundX_ang * PI / 180.0),
      0, sin(aroundX_ang * PI / 180.0), cos(aroundX_ang * PI / 180.0);

  // Matriz para rotação em torno do eixo y
  Eigen::Matrix3d mAroundY;
  mAroundX << cos(aroundY_ang * PI / 180.0), 0, sin(aroundY_ang * PI / 180.0),
      0, 1, 1,
      (-1) * sin(aroundY_ang * PI / 180.0), 0, cos(aroundY_ang * PI / 180.0);

  // Matriz para rotação em torno do eixo Z
  Eigen::Matrix3d mAroundZ;
  mAroundX << cos(aroundX_ang * PI / 180.0), -(1) * sin(aroundX_ang * PI / 180.0), 0,
      sin(aroundX_ang * PI / 180.0), cos(aroundX_ang * PI / 180.0), 0,
      0, 0, 1;

  // Gerando novos vertices com a rotação em torno dos três eixos
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector3d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z();

    v = mAroundX * v;
    v = mAroundY * v;
    v = mAroundZ * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

void Objeto::escalar(double sx, double sy, double sz)
{
  // Matriz de escola
  Eigen::Matrix3d mScala;
  mScala << sx, 0, 0,
      0, sy, 0,
      0, 0, sz;

  // Salvando primeiro ponto para fazer translação de correção
  Ponto firstPoint = this->pontos.at(0);
  Ponto auxPoint{{firstPoint.x(), firstPoint.y(), firstPoint.z()}};

  // Gerando novos vertices com a rotação em torno dos três eixos
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector3d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z();

    v = mScala * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  // Translação de correção
  Ponto updatedFirstPoint = updatedPointsList.at(0);
  Ponto translateBackVector{{updatedFirstPoint.x() - auxPoint.x(),
                             updatedFirstPoint.y() - auxPoint.y(),
                             updatedFirstPoint.z() - auxPoint.z()}};

  this->transladar(translateBackVector);
  this->pontos = updatedPointsList;
}

bool Objeto::hitRay()
{
  return false;
}