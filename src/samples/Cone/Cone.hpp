class Cone : public Objeto
{
private:
public:
  float h;    // é a altura do cone;
  float r;    // é o raio da base do cone;

  Cone(int id);
  Cone(int id, VectorXd n, float h, float r, Ponto cb);
  bool hitRay(VectorXd p0, VectorXd d, float &t_min);
  bool hitRayGetSide(VectorXd p0, VectorXd d, float &t_min, int &hitedSide);
  virtual bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
  // void cameraTransform(Eigen::Matrix4d mwc);
};