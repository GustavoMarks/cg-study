#include "RayCasting.hpp"

RGB* rayCasting(Cenario cenario, float d, int H, int W, int nlinhas, int ncolunas)
{
  RGB canvas[nlinhas][ncolunas];

  float deltaX = W / ncolunas;
  float deltaY = H / nlinhas;
  float p00x = -(W / 2) + (1 / 2) * deltaX;
  float p00y = (H / 2) - (1 / 2) * deltaY;

  for (int l = 0; l < nlinhas; l++)
  {
    Ponto plc{{0.0, p00y - l * deltaY, -d}};
    for (int c = 0; c < ncolunas; c++)
    {
      plc(0) = p00x + c * deltaX;
      Ray raio(cenario.cam.eye, plc);
      bool intersecao = raio.computarIntersecao(cenario);

      // TODO: Calcular cor e luminosidade
      if (intersecao)
      {
        canvas[l][c].r = 0;
        canvas[l][c].b = 0;
        canvas[l][c].g = 0;
      }
      else {
        canvas[l][c].r = 200;
        canvas[l][c].b = 200;
        canvas[l][c].g = 200;
      }
    }
  }

  return *canvas;
}