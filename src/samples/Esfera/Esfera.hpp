class Esfera : public Objeto
{
private:
  Ponto centro; // ponto do centro da esfera
  float r;      // raio da esfera
public:
  Esfera(int id);
  Esfera(int id, Ponto centro, float r);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min, Eigen::Vector3d &n);
};