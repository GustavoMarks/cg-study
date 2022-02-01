#include "../Ponto.hpp"
#include <vector>
#include "../../helpers/RGBIntensity/RGBIntensity.hpp"

class Objeto
{
private:
public:
  int id;
  std::vector<Ponto> pontos;

  Objeto(int id);
  Objeto(int id, std::vector<Ponto> pontos);

  void transladar(Ponto t);
  void rotacionar(int plan, double ang);
  void rotacionar(Ponto P1, Ponto P2, double ang);
  void escalar(double sx, double sy, double sz);
  void cisalhar(double ang_onX_planXYZ);
  void refletir(int plan);
  void refletir(Ponto A, Ponto B, Ponto C);
  bool hitRay(VectorXd p0, VectorXd d, float& t_min);
  void cameraTransform(Eigen::Matrix4d mwc);

  // Propriedades do material
  RGBIntesity ka = RGBIntesity(); // Coefiente para luz ambiente
  RGBIntesity kd = RGBIntesity(); // Coefiente para luz difusa
  RGBIntesity ks = RGBIntesity(); // Coefiente para luz especular
  double m;                       // Coeficiente de polimento

  void setMaterial(RGBIntesity ka, RGBIntesity kd, RGBIntesity ks, double m);
};