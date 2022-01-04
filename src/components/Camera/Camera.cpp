#include "Camera.hpp"

Camera::Camera(Ponto eye, Ponto look_at, Ponto up) : eye(eye), look_at(look_at), up(up)
{
}

Eigen::Matrix4d Camera::gerar_matriz_world_to_cam()
{
  Eigen::Vector3d w = look_at - eye;
  w.normalize();
  Eigen::Vector3d u = up * w;
  u.normalize();
  Eigen::Vector3d v = w * u;

  Eigen::Matrix4d m_world_to_cam{
      {u.x(), u.y(), u.z(), 0},
      {v.x(), v.y(), v.z(), 0},
      {w.x(), w.y(), w.z(), 0},
      {eye.x(), eye.y(), eye.z(), 1},
  };

  return m_world_to_cam;
}