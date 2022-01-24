class Esfera : public Objeto
{
private:
  Ponto p0; // known point of the sphere
  Ponto centro; // ponto do centro da esfera
  float r; // raio da esfera
public:
  Esfera(int id);
  Esfera(int id, Ponto p0, Ponto centro, float r);
  bool hitRay(VectorXd p0, VectorXd d, float& t_min);
};