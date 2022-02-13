classe Cluster {
public:
  Objeto obj_geometrico;
  vector<Cluster> clusters_filho;
  vector<Objeto> objs_filho;
  Cluster(Objeto obj_geometrico);
  void addCluster(Cluster cluster_filho);
  void addObjeto(Objeto obj_filho);
};
