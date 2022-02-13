Cluster::Cluster(Objeto obj_geometrico)
{
  this->obj_geometrico = obj_geometrico;
}

void Cluster::addCluster(Cluster cluster_filho)
{
  this->clusters_filho.push_back(cluster_filho);
}

void Cluster::addObjeto(Objeto obj_filho)
{
  this->objs_filho.push_back(obj_filho);
}
