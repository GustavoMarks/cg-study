#include "../Ponto.hpp"

class Camera
{
private:

public:
  Ponto eye;
  Ponto look_at;
  Ponto up;
  Camera(Ponto eye, Ponto look_at, Ponto up);
  Camera();
  Eigen::Matrix4d gerar_matriz_world_to_cam();
};
