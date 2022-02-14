#include "RayCasting.hpp"
#include <iostream>

using namespace std;

RGB **rayCasting(Cenario cenario, float d, int H, int W, int nlinhas, int ncolunas, bool isOrto)
{
  RGB **canvas;
  canvas = new RGB *[nlinhas];

  float deltaX = W / ncolunas;
  float deltaY = H / nlinhas;
  float p00x = -(W / 2) + ((1 / 2) * deltaX);
  float p00y = (H / 2) - ((1 / 2) * deltaY);

  cout << "executando raycasting..." << endl;

  for (int l = 0; l < nlinhas; l++)
  {
    canvas[l] = new RGB[ncolunas];
    for (int c = 0; c < ncolunas; c++)
    {
      // plc(0) = p00x + (c * deltaX);
      Ponto plc{{p00x + (c * deltaX), p00y - (l * deltaY), -d}};
      Ponto plcPartidaOrto{{p00x + (c * deltaX), p00y - (l * deltaY), 0}};
      Ponto partida = isOrto ? plcPartidaOrto : cenario.cam.eye;
      Ray raio(partida, plc);
      RGBIntesity *I = new RGBIntesity();
      bool intersecao = raio.computarIntersecao(cenario, *I);

      if (intersecao)
      {
        canvas[l][c].r = 255 * I->r;
        canvas[l][c].g = 255 * I->g;
        canvas[l][c].b = 255 * I->b;
      }
      else
      {
        canvas[l][c].r = 10;
        canvas[l][c].b = 10;
        canvas[l][c].g = 10;
      }
    }
  }

  return canvas;
}