#include "../Camera/Camera.hpp"
#include "../Objeto/Objeto.hpp"
#include <vector>

using std::vector;

class Cenario
{
public:
  Camera cam;
  vector<Objeto> objs;
  Cenario(Camera cam, vector<Objeto> objs);
  void rayCasting(float d, int H, int W, int nlinhas, int ncolunas);
};
