class Esfera : public Objeto
{
private:
  float r;      // raio da esfera
public:
  Esfera(int id);
  Esfera(int id, Ponto centro, float r);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min);
  bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
};