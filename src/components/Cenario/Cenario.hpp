#include "../Luz/LuzAmbiente.hpp"
#include "../Camera/Camera.hpp"
#include <vector>

using std::vector;

class Cenario
{
public:
  Camera cam;
  vector<Objeto *> objs;
  vector<LuzAmbiente *> luzes;
  Cenario(Camera cam, vector<Objeto *> objs, vector<LuzAmbiente *> luzes);
  void updateCamera(Camera cam);
};
