#include <iostream>

#include "./samples/samples.hpp"
#include "./helpers/IDController/IDController.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // Materiais para os objetos
    RGBIntesity *goldMaterialAmb = new RGBIntesity(0.33, 0.22, 0.03);
    RGBIntesity *goldMaterialDif = new RGBIntesity(0.75, 0.61, 0.23);
    RGBIntesity *goldMaterialSpec = new RGBIntesity(0.63, 0.56, 0.37);

    IDController *idController = new IDController();

    // Criando um cubo com 3 de aresta
    Cubo *cubo = new Cubo(3.0, idController->generateNewUID());
    cout << "Criado novo cubo de id: " << cubo->id << endl;

    // cubo->cisalhar(45);

    // Criando jarro com 6 meridianos e 6 paralelos
    Ponto p1{{1.0, 0.0, 0.0}};
    Ponto p2{{3.5, 0.5, 0.0}};
    Ponto p3{{0.0, 2.5, 0.0}};
    Ponto p4{{2.0, 3.0, 1.0}};
    CurvaBezier *jarro = new CurvaBezier(6, 6, p1, p2, p3, p4, idController->generateNewUID());
    jarro->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    cout << "Criado novo jarro de id: " << jarro->id << endl;

    // jarro->transladar(p4);
    // jarro->rotacionar(1, 45);
    // jarro->escalar(2, 2, 2);

    Ponto po{{0.0, 0.0, 0.0}};
    Ponto pe{{0.0, 0.0, 3.0}};
    Esfera *esf = new Esfera(idController->generateNewUID(), po, 3);
    esf->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    Eigen::VectorXd u{{0, 1, 0}};
    Cilindro *cil = new Cilindro(idController->generateNewUID(), po, u, 8, 4);
    cil->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    Cone *con = new Cone(idController->generateNewUID(), u, 4, 4, po);
    con->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    Cubo *cubo2 = new Cubo(2.0, idController->generateNewUID());
    cubo2->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    Ponto eye{{0, 0, 6}};
    Ponto la{{0, 0, 0}};
    Ponto lu{{10, 10, 0}};

    Camera *cam = new Camera(eye, la, lu);
    vector<Objeto *> objList;
    // objList.push_back(cubo2);
    // objList.push_back(jarro);
    objList.push_back(esf);
    // objList.push_back(cil);
    // objList.push_back(con);

    // Descrevendo luzes
    vector<LuzAmbiente *> luzList;

    RGBIntesity *luzBranca = new RGBIntesity(1, 1, 1);
    LuzAmbiente *luzAmbienteBranca = new LuzAmbiente(*luzBranca);

    Eigen::Vector3d ldr;
    ldr << 1, 0, 0;
    LuzDirecional *luzDirBranca = new LuzDirecional(*luzBranca, ldr);

    Ponto pontoDeLuz{{100, 100, 100}};
    LuzPontual *luzPontualBranca = new LuzPontual(*luzBranca, pontoDeLuz);

    // luzList.push_back(luzAmbienteBranca);
    luzList.push_back(luzDirBranca);
    // luzList.push_back(luzPontualBranca);
    Cenario *cena = new Cenario(*cam, objList, luzList);

    RGB **canvas = rayCasting(*cena, 80, 800, 800, 600, 800);
    // Abrindo uma janela com Open GL
    Window w(argc, argv, 800, 600, "CG Study", canvas);

    return 0;
}