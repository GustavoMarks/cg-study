#include "Cenario.hpp"
// #include "../Ray/Ray.hpp"
#include "../../helpers/RBG/RGB.hpp"

Cenario::Cenario(Camera cam, vector<Objeto> objs)
{
  this->cam = cam;
  this->objs = objs;
}

// void Cenario::rayCasting(float d, int H, int W, int nlinhas, int ncolunas)
// {
//   RGB canvas[nlinhas][ncolunas];

//   float deltaX = W / ncolunas;
//   float deltaY = H / nlinhas;
//   float p00x = -(W / 2) + (1 / 2) * deltaX;
//   float p00y = (H / 2) - (1 / 2) * deltaY;

//   for (int l = 0; l < nlinhas; l++)
//   {
//     Ponto plc{{0.0, p00y - l * deltaY, -d}};
//     for (int c = 0; c < ncolunas; c++)
//     {
//       plc(2) = p00x + c * deltaX;
//       Ray raio(this->cam.eye, plc);
//       bool intersecao = raio.computarIntersecao(this);
//       if (intersecao)
//       {
//         canvas[l][c].r = 0;
//         canvas[l][c].b = 0;
//         canvas[l][c].g = 0;
//       }
//       else {
//         canvas[l][c].r = 200;
//         canvas[l][c].b = 200;
//         canvas[l][c].g = 200;
//       }
      
//     }
//   }
// }