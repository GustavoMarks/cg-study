#include "Cluster.hpp"
#include <iostream>

Cluster::Cluster()
{
}

Cluster::Cluster(Objeto *obj_geometrico)
{
  this->obj_geometrico = obj_geometrico;
}

void Cluster::addCluster(Cluster cluster_filho)
{
  this->clusters_filho.push_back(cluster_filho);
}

void Cluster::addObjeto(Objeto *obj_filho)
{
  this->objs_filho.push_back(obj_filho);
}

void Cluster::cameraTransform(Eigen::Matrix4d mwc)
{
  this->obj_geometrico->cameraTransform(mwc);

  for (int i = 0; i < this->objs_filho.size(); i++)
  {
    this->objs_filho.at(i)->cameraTransform(mwc);
  }

  for (int j = 0; j < this->clusters_filho.size(); j++)
  {
    this->clusters_filho.at(j).cameraTransform(mwc);
  }
}