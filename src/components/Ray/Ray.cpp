#include "Ray.hpp"
#include <iostream>
#include <math.h>

using namespace std;
int infinito = 10000;

Ray::Ray(Ponto p0, Ponto d)
{
  this->p0 = p0;
  d.normalize();
  this->d = d;
}

void obterObjetosCluster(Cluster cluster, vector<Objeto *> &objs, Ponto p0, VectorXd d)
{
  float t_min = 123456;
  if (cluster.obj_geometrico->hitRay(p0, d, t_min))
  {
    if (cluster.clusters_filho.size() != 0)
    {
      for (int i = 0; i < cluster.clusters_filho.size(); i++)
      {
        obterObjetosCluster(cluster.clusters_filho[i], objs, p0, d);
      }
    }
    else
    {
      for (int i = 0; i < cluster.objs_filho.size(); i++)
      {
        objs.push_back(cluster.objs_filho.at(i));
      }
    }
  }
}

bool Ray::computarIntersecao(Cenario cenario, RGBIntesity &I)
{
  // vector<Objeto *> objs = cenario.objs;
  float t_min = infinito;
  float aux = infinito;
  bool finalResult = false;
  bool iResult = false;
  int objPosition = 0;

  vector<Objeto *> objs;
  obterObjetosCluster(cenario.cluster, objs, this->p0, this->d);
  for (int i = 0; i < cenario.objs.size(); i++)
  {
    objs.push_back(cenario.objs.at(i));
  }

  for (int i = 0; i < objs.size(); i++)
  {
    aux = t_min;
    iResult = objs.at(i)->hitRay(this->p0, this->d, t_min);
    if (iResult)
    {
      if (aux < t_min)
      {
        t_min = aux;
      }
      else
      {
        objPosition = i;
      }
      finalResult = iResult;
    }
  }

  // Calculando luminosidade
  if (finalResult)
  {
    // Salvando ponto de colisão com o raio de visão
    Ponto colisedPoint = this->p0 + (t_min * this->d);

    vector<LuzAmbiente *> luzes = cenario.luzes;
    for (int i = 0; i < luzes.size(); i++)
    {
      LuzAmbiente *luzAtual = luzes.at(i);
      Objeto *finded = objs.at(objPosition);

      // Luz ambiente
      if (luzAtual->luzType == 1)
      {
        // Luminosidade ambiete
        RGBIntesity Ia = luzAtual->i;
        I = I.sum(finded->ka.cross(Ia));
      }
      else
      {
        // Seperando informações do ponto de luz
        Eigen::VectorXd lightDir = luzAtual->getDir();
        Eigen::VectorXd OriginLight = luzAtual->getOriginPoint();
        // Simulando feixos de luzes paralelos da luz direcional
        if (luzAtual->luzType == 2)
          OriginLight = colisedPoint - OriginLight;

        // Tratando raios de luz em múltiplas direções de luz pontual e spot
        if (luzAtual->luzType == 3 || luzAtual->luzType == 4)
        {
          lightDir = colisedPoint - OriginLight;
          lightDir.normalize();
        }

        Eigen::Vector3d normal;

        // Verificando se o ponto do objeto é iluminado
        bool lightResult = finded->hitLight(colisedPoint, OriginLight, lightDir, normal);

        if (lightResult)
        {
          // TODO: calcular oclusão por outros objetos (sombra)
          // Calculando atenuações da luminidade
          float fad = 0;
          float fas = 0;
          Eigen::Vector3d l = luzAtual->getLightToPoint(colisedPoint);

          fad = l.dot(normal);
          fad = fad < 0 ? 0 : fad;

          Eigen::Vector3d specularR;
          specularR = (2 * fad * normal) - l;

          Eigen::Vector3d specularV;
          specularV << this->d.x(), this->d.y(), this->d.z();
          specularV = specularV * (-1);

          fas = specularV.dot(specularR);
          fas = pow(fas, finded->m);
          fas = fas < 0 ? 0 : fas;

          RGBIntesity Id = luzAtual->i.atenuar(fad);
          I = I.sum(finded->kd.cross(Id));

          RGBIntesity Is = luzAtual->i.atenuar(fas);
          I = I.sum(finded->ks.cross(Is));
        }
      }
    }
  }
  return finalResult;
}