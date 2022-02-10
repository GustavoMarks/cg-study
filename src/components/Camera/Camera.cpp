#include "Camera.hpp"

Camera::Camera(Ponto eye, Ponto look_at, Ponto up) : eye(eye), look_at(look_at), up(up)
{
}

Camera::Camera() {}

Eigen::Matrix4d Camera::gerar_matriz_world_to_cam()
{
  Eigen::Vector3d lat3d;
  lat3d << look_at.x(), look_at.y(), look_at.z();
  Eigen::Vector3d eye3d;
  eye3d << eye.x(), eye.y(), eye.z();
  Eigen::Vector3d up3d;
  up3d << up.x(), up.y(), up.z();

  Eigen::Vector3d w = eye3d - lat3d;
  w.normalize();
  Eigen::Vector3d u = up3d.cross(w);
  u.normalize();
  Eigen::Vector3d v = w.cross(u);

  // Objs.: w = k, u = i, v = j

  Eigen::Matrix4d m_world_to_cam{
      {u.x(), u.y(), u.z(), (-1) * u.dot(eye3d)},
      {v.x(), v.y(), v.z(), (-1) * v.dot(eye3d)},
      {w.x(), w.y(), w.z(), (-1) * w.dot(eye3d)},
      {0, 0, 0, 1},
  };

  return m_world_to_cam;
}

Ponto Camera::getEye()
{
  return this->eye;
}

Ponto Camera::getLook_at()
{
  return this->look_at;
}

Ponto Camera::getUp()
{
  return this->up;
}