#include "Objeto.hpp"
#include <vector>

using namespace std;

Objeto::Objeto(
    int id,
    std::vector<Face> faces)
{
  this->faces = faces;
  this->id = id;
}

int Objeto::getId(){
  return this->id;
}