#include <iostream>
#include "Cenario.hpp"
#include "../../helpers/RBG/RGB.hpp"

using namespace std;

Cenario::Cenario(Camera cam, vector<Objeto *> objs, vector<LuzAmbiente *> luzes)
{
  this->cam = cam;
  this->objs = objs;
  this->luzes = luzes;

  this->updateCamera(cam);
}

void Cenario::updateCamera(Camera cam)
{
  this->cam = cam;
  // Transformando coordenadas dos objetos para coordenadas da camera
  Eigen::Matrix4d mwc;
  mwc = cam.gerar_matriz_world_to_cam();

  cout << "Convertendo coordenadas dos objetos de mundo para câmera" << endl;

  int i;
  for (i = 0; i < this->objs.size(); i++)
  {
    this->objs.at(i)->cameraTransform(mwc);
  }

  cout << "Convertendo coordenadas das luzes de mundo para câmera" << endl;

  // for (i = 0; i < this->luzes.size(); i++)
  // {
  //   this->luzes.at(i)->cameraTransform(mwc);
  // }
}