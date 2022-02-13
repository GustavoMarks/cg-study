#include "../Objeto/Objeto.hpp"
#include <vector>

class Cluster
{
public:
  Objeto obj_geometrico;
  std::vector<Cluster> clusters_filho;
  std::vector<Objeto *> objs_filho;
  Cluster();
  Cluster(Objeto obj_geometrico);
  void addCluster(Cluster cluster_filho);
  void addObjeto(Objeto obj_filho);
};
