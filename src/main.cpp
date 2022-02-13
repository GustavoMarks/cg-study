#include <iostream>

#include "./samples/samples.hpp"
#include "./helpers/IDController/IDController.hpp"

using namespace std;

int main(int argc, char **argv)
{

    IDController *idController = new IDController();

    // Materiais para os objetos
    RGBIntesity *goldMaterialAmb = new RGBIntesity(0.33, 0.22, 0.03);
    RGBIntesity *goldMaterialDif = new RGBIntesity(0.75, 0.61, 0.23);
    RGBIntesity *goldMaterialSpec = new RGBIntesity(0.63, 0.56, 0.37);

    // // Criando um cubo com 3 de aresta
    // Cubo *cubo = new Cubo(3.0, idController->generateNewUID());
    // cout << "Criado novo cubo de id: " << cubo->id << endl;

    // // cubo->cisalhar(45);

    // // Criando jarro com 6 meridianos e 6 paralelos
    // Ponto p1{{1.0, 0.0, 0.0}};
    // Ponto p2{{3.5, 0.5, 0.0}};
    // Ponto p3{{0.0, 2.5, 0.0}};
    // Ponto p4{{2.0, 3.0, 1.0}};
    // CurvaBezier *jarro = new CurvaBezier(6, 6, p1, p2, p3, p4, idController->generateNewUID());
    // jarro->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // cout << "Criado novo jarro de id: " << jarro->id << endl;

    // // jarro->transladar(p4);
    // // jarro->rotacionar(1, 45);
    // // jarro->escalar(2, 2, 2);

    // Ponto po{{0.0, 0.0, 0.0}};
    // Ponto poc{{0, 30, 0}};
    // Ponto pe{{0.0, 0.0, 3.0}};
    // Esfera *esf = new Esfera(idController->generateNewUID(), poc, 6);
    // esf->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Eigen::VectorXd u{{0, 1, 0}};
    // Cilindro *cil = new Cilindro(idController->generateNewUID(), po, u, 6, 6);
    // cil->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Cone *con = new Cone(idController->generateNewUID(), u, 4, 4, po);
    // con->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Cubo *cubo2 = new Cubo(idController->generateNewUID(), 10);
    // cubo2->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Ponto pPlano{{0, 1, 0}};
    // Eigen::VectorXd dPlano{{0, 1, 0}};
    // Plano *plano = new Plano(idController->generateNewUID(), pPlano, dPlano);
    // plano->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Ponto p1Triang{{4, 0, 0}};
    // Ponto p2Triang{{0, 0, 4}};
    // Ponto p3Triang{{4, 0, 4}};
    // FaceTriangular *fteste = new FaceTriangular(idController->generateNewUID(), p1Triang, p2Triang, p3Triang);
    // fteste->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    // Montando câmera
    Ponto eye{{0, 0, 12}};
    Ponto la{{0, 0, 1}};
    Ponto lu{{0, 100, 0}};
    Camera *cam = new Camera(eye, la, lu);

    vector<Objeto *> objList;
    // objList.push_back(cubo2);
    // objList.push_back(jarro);
    // objList.push_back(cil);
    // objList.push_back(con);
    // objList.push_back(plano);
    // objList.push_back(fteste);
    // objList.push_back(esf);

    Eigen::VectorXd eixo_pecas{{0, 1, 0}};

    // Montando um peão
    Ponto p_basePeao{{0, 0, 0}};
    Cilindro *cil_base1_peao = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 4, 8);
    cil_base1_peao->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Cilindro *cil_base2_peao = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 8, 6);
    cil_base2_peao->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Ponto p_incio_corpo1_peao{{0, 7, 0}};
    Cone *con_corpo1_peao = new Cone(idController->generateNewUID(), eixo_pecas, 16, 4, p_incio_corpo1_peao);
    con_corpo1_peao->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Ponto p_corpo2_peao{{0, 19, 0}};
    Cilindro *cil_corpo2_peao = new Cilindro(idController->generateNewUID(), p_corpo2_peao, eixo_pecas, 1, 4);
    cil_corpo2_peao->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Ponto p_topo_peao{{0, 24, 0}};
    Esfera *esf_topo_peao = new Esfera(idController->generateNewUID(), p_topo_peao, 4);
    esf_topo_peao->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);

    objList.push_back(con_corpo1_peao);
    objList.push_back(cil_base1_peao);
    objList.push_back(cil_base2_peao);
    objList.push_back(cil_corpo2_peao);
    objList.push_back(esf_topo_peao);

    // Descrevendo luzes
    vector<LuzAmbiente *> luzList;

    RGBIntesity *luzBranca = new RGBIntesity(1, 1, 1);
    LuzAmbiente *luzAmbienteBranca = new LuzAmbiente(*luzBranca);

    Eigen::Vector3d ldr;
    ldr << -1, -1, 0;
    LuzDirecional *luzDirBranca = new LuzDirecional(*luzBranca, ldr);

    Ponto pontoDeLuz{{100, 100, 100}};
    LuzPontual *luzPontualBranca = new LuzPontual(*luzBranca, pontoDeLuz);

    luzList.push_back(luzAmbienteBranca);
    luzList.push_back(luzDirBranca);
    // luzList.push_back(luzPontualBranca);
    Cenario *cena = new Cenario(*cam, objList, luzList);

    // Abrindo uma janela com Open GL
    Window w(argc, argv, 800, 600, "CG Study", cena);

    return 0;
}