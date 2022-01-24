#include "../Ponto.hpp"
#include "../Cenario/Cenario.hpp"

class Ray
{
public:
  Ponto p0; // ponto de origem do raio, geralmente é o ponto eye da camera
  Ponto d; // vetor unitario que determina a direcao do raio
  Ray(Ponto p0, Ponto d);
  bool computarIntersecao(Cenario cenario);
};
