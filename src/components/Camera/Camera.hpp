#include "../Ponto.hpp"

class Camera
{
private:
  Ponto eye;
  Ponto look_at;
  Ponto up;

public:
  Camera(Ponto eye, Ponto look_at, Ponto up);
  Eigen::Matrix4d gerar_matriz_world_to_cam();
};
