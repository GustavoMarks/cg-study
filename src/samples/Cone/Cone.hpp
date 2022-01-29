class Cone : public Objeto
{
private:

public:
  Ponto V; // é o vértice do cone;
  VectorXd n; // é o vetor unitário que define a direção e o sentido do eixo do cone;
  float h; // é a altura do cone;
  float r; // é o raio da base do cone;
  Ponto cb; // é o centro da base do cone;

  Cone(int id);
  Cone(int id, VectorXd n, float h,  float r, Ponto cb);
  bool hitRay(VectorXd p0, VectorXd d, float &t_int);
};