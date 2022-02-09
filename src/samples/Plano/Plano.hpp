class Plano : public Objeto
{
private:
  /* data */
public:
  VectorXd n; // é o vetor unitário perpendicular ao plano;
  Plano(int id);
  Plano(int id, Ponto p0, VectorXd n);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min);
  bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
};