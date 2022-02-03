#include "Ray.hpp"
#include <iostream>
#include <math.h>

using namespace std;

Ray::Ray(Ponto p0, Ponto d)
{
  this->p0 = p0;
  d.normalize();
  this->d = d;
}

bool Ray::computarIntersecao(Cenario cenario, RGBIntesity &I)
{
  Eigen::Vector3d normalFake;
  vector<Objeto *> objs = cenario.objs;
  float t_min = 0;
  float aux = 0;
  bool finalResult = false;
  bool iResult = false;
  int objPosition = 0;
  for (int i = 0; i < objs.size(); i++)
  {
    aux = t_min;
    iResult = objs.at(i)->hitRay(this->p0, this->d, t_min, normalFake);
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

  // Salvando ponto de colisão com o raio
  Ponto colisedPoint = this->p0 + (t_min * this->d);

  // Calculando luminosidade
  if (finalResult)
  {
    vector<LuzAmbiente *> luzes = cenario.luzes;
    for (int i = 0; i < luzes.size(); i++)
    {
      LuzAmbiente *luzAtual = luzes.at(i);
      Objeto *finded = objs.at(objPosition);

      if (luzAtual->isAmbiente)
      {
        // Luminosidade ambiete
        RGBIntesity Ia = luzAtual->i;
        I = I.sum(finded->ka.cross(Ia));
      }
      else
      {
        // Calculando fator de atenuação difuso e especular
        float fad = 0;
        float fas = 0;
        float t_min_light_to_obj = 0;
        Eigen::Vector3d normal;

        Eigen::Vector3d originLight3d = luzAtual->getOriginPoint();
        Eigen::VectorXd originLight{{originLight3d.x(), originLight3d.y(), originLight3d.z()}};

        Eigen::Vector3d l = luzAtual->getLightToPoint(colisedPoint);
        Eigen::VectorXd lightDir{{l.x(), l.y(), l.z()}};
        lightDir = lightDir * (-1);

        // Buscando normal e verficação se luz atinge objeto
        if (finded->hitRay(originLight, lightDir, t_min_light_to_obj, normal))
        {
          // Percorrendo outros objetos do cenário para verficar oclusão (sombra)
          float t_min_light = 10000;
          float aux2 = 10000;
          for (int j = 0; j < objs.size(); j++)
          {
            if (j != objPosition)
            {
              aux2 = t_min_light;
              objs.at(j)->hitRay(originLight, lightDir, t_min_light, normalFake);
              t_min_light = aux2 < t_min_light ? aux2 : t_min_light;
            }
          }

          // Caso de não oclusão, calculando atenuações
          if (t_min_light_to_obj <= t_min_light)
          {
            fad = l.dot(normal);
            fad = fad < 0 ? 0 : fad;
            
            Eigen::Vector3d specularR;
            specularR = (2 * (fad)*normal) - l;
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
  }

  return finalResult;
}