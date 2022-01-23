#include "Cenario.hpp"
#include "../../helpers/RBG/RGB.hpp"

Cenario::Cenario(Camera cam, vector<Objeto> objs)
{
  this->cam = cam;
  this->objs = objs;
}