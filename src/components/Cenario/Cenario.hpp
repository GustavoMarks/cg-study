#include "../Camera/Camera.hpp"
#include "../Malha/Malha.hpp"
#include <vector>

using std::vector;

class Cenario
{
public:
  Camera cam;
  vector<Objeto*> objs;
  Cenario(Camera cam, vector<Objeto*> objs);
  void updateCamera(Camera cam);
};
