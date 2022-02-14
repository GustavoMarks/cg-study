#include "../Ponto.hpp"
#include <vector>
#include "../../helpers/RGBIntensity/RGBIntensity.hpp"

class Objeto
{
private:
public:
  int id;
  std::vector<Ponto> pontos;

  Objeto();
  Objeto(int id);
  Objeto(int id, std::vector<Ponto> pontos);

  virtual void transladar(Ponto t);
  virtual void rotacionar(int axis, double ang);
  virtual void rotacionar(Ponto P1, Ponto P2, double ang);
  virtual void escalar(double sx, double sy, double sz);
  virtual void cisalhar(double ang_onX_planXYZ);
  virtual void refletir(int plan);
  virtual void refletir(Ponto A, Ponto B, Ponto C);
  virtual bool hitRay(VectorXd p0, VectorXd d, float &t_min);
  virtual bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
  virtual void cameraTransform(Eigen::Matrix4d mwc);

  // Propriedades do material
  RGBIntesity ka = RGBIntesity(); // Coefiente para luz ambiente
  RGBIntesity kd = RGBIntesity(); // Coefiente para luz difusa
  RGBIntesity ks = RGBIntesity(); // Coefiente para luz especular
  double m;                       // Coeficiente de polimento

  void setMaterial(RGBIntesity ka, RGBIntesity kd, RGBIntesity ks, double m);
};