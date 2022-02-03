class Cilindro : public Objeto
{
private:
  Ponto b;    // o centro da base do cilindro
  VectorXd u; // é o vetor unitário que define a direção e o sentido do eixo do cilindro;
  float h;    // é a altura do cilindro
  float r;    // é a raio do cilindro
public:
  Cilindro(int id);
  Cilindro(int id, Ponto b, VectorXd u, float h, float r);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min, Eigen::Vector3d &n);
};