#include "Objeto.hpp"
#include "../CurvasParametricas/CurvasParametricas.hpp"
#include <vector>

#define PI 3.14159265

using namespace std;

Objeto::Objeto(
    int id,
    std::vector<Face> faces)
{
  this->faces = faces;
  this->id = id;
}

Objeto::Objeto(int id)
{
  this->id = id;
}

std::ostream &operator<<(std::ostream &os, Objeto &obj)
{
  os << "Objeto id = " << obj.id << endl;
  os << "-Faces: " << endl;

  int i = 0;
  for (auto it = obj.faces.begin(); it != obj.faces.end(); it++, i++)
  {
    Aresta a0 = get<0>(*it);
    Ponto p0_a0 = get<0>(a0);
    Ponto p1_a0 = get<1>(a0);

    Aresta a1 = get<1>(*it);
    Ponto p0_a1 = get<0>(a1);
    Ponto p1_a1 = get<1>(a1);

    Aresta a2 = get<2>(*it);
    Ponto p0_a2 = get<0>(a2);
    Ponto p1_a2 = get<1>(a2);

    os << "--Face " << i << ": " << endl;

    os << "---Aresta 1: " << endl;
    os << "----Vertice 1: " << p0_a0 << endl;
    os << "----Vertice 2: " << p1_a0 << endl;

    os << "---Aresta 2: " << endl;
    os << "----Vertice 1: " << p0_a1 << endl;
    os << "----Vertice 2: " << p0_a1 << endl;

    os << "---Aresta 3: " << endl;
    os << "----Vertice 1: " << p0_a2 << endl;
    os << "----Vertice 2: " << p0_a2 << endl;
  }

  return os;
}

int Objeto::getId()
{
  return this->id;
}

void Objeto::criarCurvaBezier(
    Ponto p0,
    Ponto p1,
    Ponto p2,
    Ponto p3)
{
  int num_paralelos = 20;
  int num_meridianos = 20;

  // preenchendo os vertices
  std::vector<Ponto> vertices;
  for (int j = 0; j <= num_paralelos; j++)
  {
    // t is the parameter in the range from 0 to 1 to mark the points
    int t = (1.0 / num_paralelos) * j;
    double z = p0[1] * b_1(t) + p1[1] * b_2(t) + p2[1] * b_3(t) + p3[1] * b_4(t);

    for (int i = 0; i <= num_meridianos; i++)
    {
      double r = p0[0] * b_1(t) + p1[0] * b_2(t) + p2[0] * b_3(t) + p3[0] * b_4(t);

      // Coordinates x, y, z of the vertices defined when a parallel
      // circle crosses a meridian profile curve.
      double x = r * cos((2.0 * PI / num_meridianos) * (float)i);
      double y = r * cos((2.0 * PI / num_meridianos) * (float)i);
      Ponto p{{x, y, z}};

      vertices.push_back(p);
    }
  }

  // preenchendo as faces com arestas no sentido anti-horario
  std::vector<Face> faces;
  int num_quadrados = (num_meridianos - 1) * (num_paralelos - 1);
  // cada quadrado tem duas faces triangulares
  for (int i = 0; i < num_quadrados; i++)
  {
    for (int j = num_meridianos * i; j < (num_meridianos * i + 1) - 1; j++)
    {
      Ponto p_esq_inf = vertices[j];
      Ponto p_dir_inf = vertices[j + 1];
      Ponto p_esq_sup = vertices[j + num_meridianos];
      Ponto p_dir_sup = vertices[j + 1 + num_meridianos];
      Aresta a_diagonal = make_pair(p_esq_inf, p_dir_sup);

      // face triagular inferior
      Aresta a1 = make_pair(p_esq_inf, p_dir_inf);
      Aresta a2 = make_pair(p_dir_inf, p_dir_sup);
      Face f1 = make_tuple(a_diagonal, a1, a2);

      // face triagular superior
      Aresta a3 = make_pair(p_esq_sup, p_dir_sup);
      Aresta a4 = make_pair(p_esq_sup, p_esq_inf);
      Face f2 = make_tuple(a3, a4, a_diagonal);

      faces.push_back(f1);
      faces.push_back(f2);
    }
  }

  this->faces = faces;
}