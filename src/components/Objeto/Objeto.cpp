#include <iostream>
#include <eigen-3.4.0/Eigen/Dense>
#include <math.h>
#include "Objeto.hpp"

#define PI 3.14159265

using namespace std;

Objeto::Objeto(int id)
{
  this->id = id;
  this->ka = RGBIntesity();
  this->kd = RGBIntesity();
  this->ks = RGBIntesity();
}

Objeto::Objeto(int id, std::vector<Ponto> pontos)
{
  this->pontos = pontos;
  this->id = id;
  this->ka = RGBIntesity();
  this->kd = RGBIntesity();
  this->ks = RGBIntesity();
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

// Inteiro para selecionar eixo do rotação
// 0 = X; 1 = Y; 2 = Z
void Objeto::rotacionar(int axis, double ang)
{
  // Matriz para rotação em torno do eixo X
  // OBS.: Entrada das funções é em radianos, fazendo conversão dos parâmentros
  Eigen::Matrix3d r;

  switch (axis)
  {
  case 0:
    r << 1, 0, 0,
        0, cos(ang * PI / 180.0), (-1) * sin(ang * PI / 180.0),
        0, sin(ang * PI / 180.0), cos(ang * PI / 180.0);
    break;

  case 1:
    r << cos(ang * PI / 180.0), 0, sin(ang * PI / 180.0),
        0, 1, 1,
        (-1) * sin(ang * PI / 180.0), 0, cos(ang * PI / 180.0);
    break;

  case 2:
    r << cos(ang * PI / 180.0), -(1) * sin(ang * PI / 180.0), 0,
        sin(ang * PI / 180.0), cos(ang * PI / 180.0), 0,
        0, 0, 1;
    break;

  default:
    break;
  }

  // Gerando novos vertices com a rotação em torno dos três eixos
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector3d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z();

    v = r * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

// Rotação em torno de um eixo arbitrário que passa pelos pontos P1 e P2
void Objeto::rotacionar(Ponto P1, Ponto P2, double ang)
{
  // Encontrado vetor unitário do eixo
  Eigen::Vector3d k;
  Ponto P = P2 - P1;
  Eigen::Vector3d P3d;
  P3d << P.x(), P.y(), P.z();
  k << P / P.norm();

  // Encontrando sistema de coordenadas
  Eigen::Vector3d w;
  w << -k.x(), k.y(), k.z();
  Eigen::Vector3d q;
  q = w.cross(k);
  Eigen::Vector3d i;
  i << q / q.norm();
  Eigen::Vector3d j;
  j = k.cross(i);

  // Criando matrizes de mudanças de coordenadas
  Eigen::Matrix4d mxxl;
  mxxl << i.x(), i.y(), i.z(), (-1) * P1.dot(i),
      j.x(), j.y(), i.z(), (-1) * P1.dot(j),
      k.x(), k.y(), k.z(), (-1) * P1.dot(k),
      0, 0, 0, 1;

  Eigen::Matrix4d mxlx;
  mxxl << i.x(), j.x(), k.x(), P1.x(),
      i.y(), j.y(), k.y(), P1.y(),
      i.z(), j.z(), k.z(), P1.z(),
      0, 0, 0, 1;

  // Matriz de rotação em torno do eixo z
  Eigen::Matrix4d mrz;
  mrz << cos(ang * PI / 180.0), -(1) * sin(ang * PI / 180.0), 0,
      sin(ang * PI / 180.0), cos(ang * PI / 180.0), 0,
      0, 0, 1;

  // Criando novos vértices
  vector<Ponto> updatedPointsList;
  int pointer;
  for (pointer = 0; pointer < this->pontos.size(); pointer++)
  {
    Eigen::Vector4d v;
    Ponto p = this->pontos.at(pointer);

    v << p.x(), p.y(), p.z(), 1;

    v = mxlx * (mrz * (mxxl * v));
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

void Objeto::escalar(double sx, double sy, double sz)
{
  // Matriz de escalar
  Eigen::Matrix3d mScala;
  mScala << sx, 0, 0,
      0, sy, 0,
      0, 0, sz;

  // Salvando primeiro ponto para fazer translação de correção
  Ponto firstPoint = this->pontos.at(0);
  Ponto auxPoint{{firstPoint.x(), firstPoint.y(), firstPoint.z()}};

  // Gerando novos vertices
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

// Cisalhamento acontece com transformação em direção ao eixo X com plano padrão xyz
// Para outros planos e outras direções de deformação aplicar rotação prévia
void Objeto::cisalhar(double ang_onX_planXYZ)
{
  // Matriz de cisalhamento
  // OBS.: Entrada das funções é em radianos, fazendo conversão dos parâmentros
  Eigen::Matrix3d c;
  c << 1, tan(ang_onX_planXYZ * PI / 180.0), 0,
      0, 1, 0,
      0, 0, 1;

  // Gerando novos vertices
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector3d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z();

    v = c * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

// Inteiro para selecionar plano do espelho
// 0 = XY; 1 = XZ; 2 = YZ
void Objeto::refletir(int plan)
{
  // Matriz de espelhamento
  Eigen::Matrix3d e;

  switch (plan)
  {
  case 0:
    e << 1, 0, 0,
        0, 1, 0,
        0, 0, -1;
    break;
  case 1:
    e << 1, 0, 0,
        0, -1, 0,
        0, 0, 1;
    break;
  case 2:
    e << -1, 0, 0,
        0, 1, 0,
        0, 0, 1;
    break;
  default:
    break;
  }

  // Gerando novos vertices
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector3d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z();

    v = e * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

// Reflexão em torno de plano arbitrário formado pelos potnos ABC
void Objeto::refletir(Ponto A, Ponto B, Ponto C)
{
  // Adaptando pontos do plano para 4d
  Eigen::Vector4d A4d;
  A4d << A.x(), A.y(), A.z(), 1;
  Eigen::Vector4d B4d;
  B4d << B.x(), B.y(), B.z(), 1;
  Eigen::Vector4d C4d;
  C4d << C.x(), C.y(), C.z(), 1;

  // Fazendo traslação para que plano do espelho passe pela origem
  Eigen::Vector4d paT{{0, 0, 0, 1}};
  Eigen::Matrix4d mtAO;
  mtAO << 1, 0, 0, -A.x(),
      0, 1, 0, -A.y(),
      0, 0, 1, -A.z(),
      0, 0, 0, 1;

  // Guardando transposta para aplicação
  Eigen::Matrix4d mtAO_t;
  mtAO_t = mtAO.transpose();

  Eigen::Vector4d pbT;
  pbT = mtAO * B4d;
  Eigen::Vector3d pbT3d;
  pbT3d << pbT(0), pbT(1), pbT(2);

  Eigen::Vector4d pcT;
  pcT = mtAO * C4d;
  Eigen::Vector3d pcT3d;
  pcT3d << pcT(0), pcT(1), pcT(2);

  // Criando matriz de HousedHolder
  Eigen::Vector3d N;
  N = pbT3d.cross(pcT3d);
  Eigen::Vector3d n;
  n = N / N.norm();
  Eigen::Vector4d n4d;
  n4d << n(0), n(1), n(2), 1;
  Eigen::Matrix4d I = Eigen::Matrix4d::Identity(4, 4);

  Eigen::Matrix4d H;
  H = I - (2 * n4d * n4d.transpose());

  // Criando novos vértices
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector4d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z(), 1;

    v = mtAO_t * H * mtAO * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

bool Objeto::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
  // cout << "método pai chamado..." << endl;
  return false;
}

void Objeto::cameraTransform(Eigen::Matrix4d mwc)
{
  // Gerando novos vertices
  vector<Ponto> updatedPointsList;
  int i;
  for (i = 0; i < this->pontos.size(); i++)
  {
    Eigen::Vector4d v;
    Ponto p = this->pontos.at(i);

    v << p.x(), p.y(), p.z(), 1;

    v = mwc * v;
    Ponto updatePoint{{v(0), v(1), v(2)}};

    updatedPointsList.push_back(updatePoint);
  }

  this->pontos = updatedPointsList;
}

void Objeto::setMaterial(RGBIntesity ka, RGBIntesity kd, RGBIntesity ks, double m)
{
  this->ka = ka;
  this->kd = kd;
  this->ks = ks;
  this->m = m < 0 ? 1 : m;
}