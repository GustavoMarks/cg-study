class Cilindro : public Objeto
{
private:
  VectorXd u; // é o vetor unitário que define a direção e o sentido do eixo do cilindro;
  float h;    // é a altura do cilindro
  float r;    // é a raio do cilindro
public:
  Cilindro(int id);
  Cilindro(int id, Ponto b, VectorXd u, float h, float r);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min);
  bool hitRayGetSide(VectorXd p0, VectorXd d, float &t_min, int &hitedSide);
  virtual bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
};