#include "../Luz/Luz.hpp"
#include "../Camera/Camera.hpp"
#include "../Cluster/Cluster.hpp"
#include <vector>

using std::vector;

class Cenario
{
public:
  Camera cam;
  Cluster cluster;
  vector<Objeto *> objs;
  vector<LuzAmbiente *> luzes;
  Cenario(Camera cam, vector<Objeto *> objs, vector<LuzAmbiente *> luzes, Cluster cluster);
  void updateCamera(Camera cam);
  Camera getCamera();
};
