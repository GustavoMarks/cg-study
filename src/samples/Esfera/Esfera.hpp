
class Esfera : public Objeto
{
private:
  Ponto p0; // known point of the sphere
  Ponto centro; // ponto do centro da esfera
  float r; // raio da esfera
public:
  Esfera();
  Esfera(Ponto p0, Ponto centro, float r);
  bool hitRay(Ray raio, float& t_min);
};