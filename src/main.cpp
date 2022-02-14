#include <iostream>

#include "./samples/samples.hpp"
#include "./helpers/IDController/IDController.hpp"

using namespace std;

// Materiais para os objetos
// Ouro:
RGBIntesity *goldMaterialAmb = new RGBIntesity(0.33, 0.22, 0.03);
RGBIntesity *goldMaterialDif = new RGBIntesity(0.75, 0.61, 0.23);
RGBIntesity *goldMaterialSpec = new RGBIntesity(0.63, 0.56, 0.37);
// Madeira escura:
RGBIntesity *woodMaterialAmb = new RGBIntesity(0.14, 0.09, 0.06);
RGBIntesity *woodMaterialDif = new RGBIntesity(0.01, 0.01, 0.01);
RGBIntesity *woodMaterialSpec = new RGBIntesity(0.1, 0.1, 0.1);
// Plástico preto:
RGBIntesity *blackPlasticAmb = new RGBIntesity(0, 0, 0);
RGBIntesity *blackPlasticDif = new RGBIntesity(0.01, 0.01, 0.01);
RGBIntesity *blackPlasticSpec = new RGBIntesity(0.50, 0.50, 0.50);
// Pérola
RGBIntesity *perlAmb = new RGBIntesity(0.25, 0.20, 0.20);
RGBIntesity *perlDif = new RGBIntesity(1, 0.83, 0.83);
RGBIntesity *perlSpec = new RGBIntesity(0.29, 0.29, 0.29);
// Prata
RGBIntesity *silverAmb = new RGBIntesity(0.23, 0.23, 0.23);
RGBIntesity *silverDif = new RGBIntesity(0.27, 0.27, 0.27);
RGBIntesity *silverSpec = new RGBIntesity(0.77, 0.77, 0.77);

IDController *idController = new IDController();

void montarTabuleiro(vector<Objeto *> &objList)
{
    // Criando tabuleiro de madeira
    Cubo *tabMadeira = new Cubo(idController->generateNewUID(), 240, 6, 240);
    tabMadeira->setMaterial(*woodMaterialAmb, *woodMaterialDif, *woodMaterialSpec, 1);

    Ponto transOrigemCubo{{-120, -7, -120}};
    tabMadeira->transladar(transOrigemCubo);

    objList.push_back(tabMadeira);

    // Criando casas de plástico preto e pérola de forma iterativa
    bool isWhite = false;
    float xCoord = -96;
    float zCoord = -96;
    for (int i = 0; i < 8; i++)
    {
        float aux = xCoord;
        for (int j = 0; j < 8; j++)
        {
            if (!isWhite)
            {
                Ponto p1{{aux, 0, zCoord}};
                Ponto p2{{aux, 0, zCoord + 24}};
                Ponto p3{{aux + 24, 0, zCoord}};
                FaceTriangular *f1 = new FaceTriangular(idController->generateNewUID(), p1, p2, p3);
                f1->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);

                objList.push_back(f1);

                Ponto p4{{aux + 24, 0, zCoord + 24}};
                FaceTriangular *f2 = new FaceTriangular(idController->generateNewUID(), p2, p4, p3);
                f2->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);

                objList.push_back(f2);
            }
            else
            {
                // Ponto p1{{aux, 0, zCoord}};
                // Ponto p2{{aux, 0, zCoord + 12}};
                // Ponto p3{{aux + 12, 0, zCoord}};
                // FaceTriangular *f1 = new FaceTriangular(idController->generateNewUID(), p1, p2, p3);
                // f1->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);

                // objList.push_back(f1);

                // Ponto p4{{aux + 12, 0, zCoord + 12}};
                // FaceTriangular *f2 = new FaceTriangular(idController->generateNewUID(), p2, p4, p3);
                // f2->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);

                // objList.push_back(f2);
            }

            isWhite = !isWhite;
            aux = aux + 24;
        }

        isWhite = !isWhite;
        zCoord = zCoord + 24;
    }
}

void montarPecas(vector<Objeto *> &objList)
{
    Eigen::VectorXd eixo_pecas{{0, 1, 0}};

    // Montando um peão
    Ponto p_basePeao{{0, 0, 0}};
    Cilindro *cil_base1_peao = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 4, 8);
    cil_base1_peao->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Cilindro *cil_base2_peao = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 8, 6);
    cil_base2_peao->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_incio_corpo1_peao{{0, 7, 0}};
    Cone *con_corpo1_peao = new Cone(idController->generateNewUID(), eixo_pecas, 16, 4, p_incio_corpo1_peao);
    con_corpo1_peao->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_corpo2_peao{{0, 19, 0}};
    Cilindro *cil_corpo2_peao = new Cilindro(idController->generateNewUID(), p_corpo2_peao, eixo_pecas, 1, 4);
    cil_corpo2_peao->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_topo_peao{{0, 24, 0}};
    Esfera *esf_topo_peao = new Esfera(idController->generateNewUID(), p_topo_peao, 4);
    esf_topo_peao->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);

    Ponto toTranslate{{-60, 0, -36}};
    con_corpo1_peao->transladar(toTranslate);
    cil_base1_peao->transladar(toTranslate);
    cil_base2_peao->transladar(toTranslate);
    cil_corpo2_peao->transladar(toTranslate);
    esf_topo_peao->transladar(toTranslate);

    objList.push_back(con_corpo1_peao);
    objList.push_back(cil_base1_peao);
    objList.push_back(cil_base2_peao);
    objList.push_back(cil_corpo2_peao);
    objList.push_back(esf_topo_peao);

    Cone *con_corpo1_peao4 = new Cone(idController->generateNewUID(), eixo_pecas, 16, 4, p_incio_corpo1_peao);
    con_corpo1_peao4->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_base1_peao4 = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 4, 8);
    cil_base1_peao4->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_base2_peao4 = new Cilindro(idController->generateNewUID(), p_basePeao, eixo_pecas, 8, 6);
    cil_base2_peao4->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_corpo2_peao4 = new Cilindro(idController->generateNewUID(), p_corpo2_peao, eixo_pecas, 1, 4);
    cil_base1_peao4->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Esfera *esf_topo_peao4 = new Esfera(idController->generateNewUID(), p_topo_peao, 4);
    esf_topo_peao4->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);

    // Refletindo no plato yz e em seguida no plano xy
    con_corpo1_peao4->transladar(toTranslate);
    cil_base1_peao4->transladar(toTranslate);
    cil_base2_peao4->transladar(toTranslate);
    cil_corpo2_peao4->transladar(toTranslate);
    esf_topo_peao4->transladar(toTranslate);
    con_corpo1_peao4->refletir(2);
    cil_base1_peao4->refletir(2);
    cil_base2_peao4->refletir(2);
    cil_corpo2_peao4->refletir(2);
    esf_topo_peao4->refletir(2);
    con_corpo1_peao4->refletir(0);
    cil_base1_peao4->refletir(0);
    cil_base2_peao4->refletir(0);
    cil_corpo2_peao4->refletir(0);
    esf_topo_peao4->refletir(0);

    objList.push_back(con_corpo1_peao4);
    objList.push_back(cil_base1_peao4);
    objList.push_back(cil_base2_peao4);
    objList.push_back(cil_corpo2_peao4);
    objList.push_back(esf_topo_peao4);

    // Montando uma torre
    Ponto p_baseTorre{{0, 0, 0}};
    Cilindro *cil_base1_torre = new Cilindro(idController->generateNewUID(), p_baseTorre, eixo_pecas, 4, 8);
    cil_base1_torre->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Cilindro *cil_base2_torre = new Cilindro(idController->generateNewUID(), p_baseTorre, eixo_pecas, 8, 6);
    cil_base2_torre->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_incio_corpo1_torre{{0, 7, 0}};
    Cone *con_corpo1_torre = new Cone(idController->generateNewUID(), eixo_pecas, 26, 6, p_incio_corpo1_torre);
    con_corpo1_torre->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_topo_torre{{0, 26, 0}};
    Cilindro *cil_topo_torre = new Cilindro(idController->generateNewUID(), p_topo_torre, eixo_pecas, 6, 4);
    cil_topo_torre->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);

    Ponto toTranslateTorre{{-84, 0, 84}};
    con_corpo1_torre->transladar(toTranslateTorre);
    cil_base1_torre->transladar(toTranslateTorre);
    cil_base2_torre->transladar(toTranslateTorre);
    cil_topo_torre->transladar(toTranslateTorre);

    objList.push_back(con_corpo1_torre);
    objList.push_back(cil_base1_torre);
    objList.push_back(cil_base2_torre);
    objList.push_back(cil_topo_torre);

    // Montando um "cavalo"
    Ponto p_baseCavalo{{0, 0, 0}};
    Cilindro *cil_base1_cavalo = new Cilindro(idController->generateNewUID(), p_baseCavalo, eixo_pecas, 4, 8);
    cil_base1_cavalo->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_base2_cavalo = new Cilindro(idController->generateNewUID(), p_baseCavalo, eixo_pecas, 8, 6);
    cil_base2_cavalo->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_incio_corpo1_cavalo{{0, 7, 0}};
    Cone *con_corpo1_cavalo = new Cone(idController->generateNewUID(), eixo_pecas, 26, 8, p_incio_corpo1_cavalo);
    con_corpo1_cavalo->cisalhar(10);
    con_corpo1_cavalo->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_topo_cavalo{{4, 28, 0}};
    Eigen::VectorXd eixo_cabeca_cavalo{{-1, 0, 0}};
    Cilindro *cil_topo_cavalo = new Cilindro(idController->generateNewUID(), p_topo_cavalo, eixo_cabeca_cavalo, 8, 3);
    cil_topo_cavalo->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);

    Ponto toTranslateCavalo{{84, 0, 60}};
    con_corpo1_cavalo->transladar(toTranslateCavalo);
    cil_base1_cavalo->transladar(toTranslateCavalo);
    cil_base2_cavalo->transladar(toTranslateCavalo);
    cil_topo_cavalo->transladar(toTranslateCavalo);

    objList.push_back(con_corpo1_cavalo);
    objList.push_back(cil_base1_cavalo);
    objList.push_back(cil_base2_cavalo);
    objList.push_back(cil_topo_cavalo);

    // Montando um bispo
    Ponto p_baseBispo{{0, 0, 0}};
    Cilindro *cil_base1_bispo = new Cilindro(idController->generateNewUID(), p_baseBispo, eixo_pecas, 4, 8);
    cil_base1_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Cilindro *cil_base2_bispo = new Cilindro(idController->generateNewUID(), p_baseBispo, eixo_pecas, 8, 6);
    cil_base2_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_incio_corpo1_bispo{{0, 7, 0}};
    Cone *con_corpo1_bispo = new Cone(idController->generateNewUID(), eixo_pecas, 26, 4, p_incio_corpo1_bispo);
    con_corpo1_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_corpo2_bispo{{0, 23, 0}};
    Cilindro *cil_corpo2_bispo = new Cilindro(idController->generateNewUID(), p_corpo2_bispo, eixo_pecas, 1, 4);
    cil_corpo2_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_topo_bispo{{0, 28, 0}};
    Esfera *esf_topo_bispo = new Esfera(idController->generateNewUID(), p_topo_bispo, 4);
    esf_topo_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);
    Ponto p_topo2_bispo{{0, 30, 0}};
    Cone *con_topo2_bispo = new Cone(idController->generateNewUID(), eixo_pecas, 6, 4, p_topo2_bispo);
    con_topo2_bispo->setMaterial(*blackPlasticAmb, *blackPlasticDif, *blackPlasticSpec, 32);

    Ponto toTranslateBispo{{-84, 0, -36}};
    con_corpo1_bispo->transladar(toTranslateBispo);
    cil_base1_bispo->transladar(toTranslateBispo);
    cil_base2_bispo->transladar(toTranslateBispo);
    cil_corpo2_bispo->transladar(toTranslateBispo);
    esf_topo_bispo->transladar(toTranslateBispo);
    con_topo2_bispo->transladar(toTranslateBispo);

    objList.push_back(con_corpo1_bispo);
    objList.push_back(cil_base1_bispo);
    objList.push_back(cil_base2_bispo);
    objList.push_back(cil_corpo2_bispo);
    objList.push_back(esf_topo_bispo);
    objList.push_back(con_topo2_bispo);

    // Montando uma rainha
    Ponto p_baseRainha{{0, 0, 0}};
    Cilindro *cil_base1_rainha = new Cilindro(idController->generateNewUID(), p_baseRainha, eixo_pecas, 4, 8);
    cil_base1_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_base2_rainha = new Cilindro(idController->generateNewUID(), p_baseRainha, eixo_pecas, 8, 6);
    cil_base2_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_incio_corpo1_rainha{{0, 7, 0}};
    Cone *con_corpo1_rainha = new Cone(idController->generateNewUID(), eixo_pecas, 28, 4, p_incio_corpo1_rainha);
    con_corpo1_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_corpo2_rainha{{0, 25, 0}};
    Cilindro *cil_corpo2_rainha = new Cilindro(idController->generateNewUID(), p_corpo2_rainha, eixo_pecas, 1, 4);
    cil_corpo2_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_topo1_rainha{{0, 32, 0}};
    Cone *con_topo1_rainha = new Cone(idController->generateNewUID(), (-1) * eixo_pecas, 8, 6, p_topo1_rainha);
    con_topo1_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_topo_rainha{{0, 34, 0}};
    Esfera *esf_topo_rainha = new Esfera(idController->generateNewUID(), p_topo_rainha, 2);
    esf_topo_rainha->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);

    Ponto toTranslateRainha{{84, 0, 12}};
    con_corpo1_rainha->transladar(toTranslateRainha);
    cil_base1_rainha->transladar(toTranslateRainha);
    cil_base2_rainha->transladar(toTranslateRainha);
    cil_corpo2_rainha->transladar(toTranslateRainha);
    esf_topo_rainha->transladar(toTranslateRainha);
    con_topo1_rainha->transladar(toTranslateRainha);

    objList.push_back(con_corpo1_rainha);
    objList.push_back(cil_base1_rainha);
    objList.push_back(cil_base2_rainha);
    objList.push_back(cil_corpo2_rainha);
    objList.push_back(esf_topo_rainha);
    objList.push_back(con_topo1_rainha);

    // Montando um rei
    Ponto p_baseRei{{0, 0, 0}};
    Cilindro *cil_base1_rei = new Cilindro(idController->generateNewUID(), p_baseRei, eixo_pecas, 4, 8);
    cil_base1_rei->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Cilindro *cil_base2_rei = new Cilindro(idController->generateNewUID(), p_baseRei, eixo_pecas, 8, 6);
    cil_base2_rei->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_incio_corpo1_rei{{0, 7, 0}};
    Cone *con_corpo1_rei = new Cone(idController->generateNewUID(), eixo_pecas, 28, 4, p_incio_corpo1_rei);
    con_corpo1_rei->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_corpo2_rei{{0, 25, 0}};
    Cilindro *cil_corpo2_rei = new Cilindro(idController->generateNewUID(), p_corpo2_rei, eixo_pecas, 1, 4);
    cil_corpo2_rei->setMaterial(*perlAmb, *perlDif, *perlSpec, 11);
    Ponto p_topo1_rei{{0, 34, 0}};
    Cone *con_topo1_rei = new Cone(idController->generateNewUID(), (-1) * eixo_pecas, 8, 6, p_topo1_rei);
    con_topo1_rei->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Cilindro *cil_topo2_rei = new Cilindro(idController->generateNewUID(), p_topo1_rei, eixo_pecas, 6, 1);
    cil_topo2_rei->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    Eigen::VectorXd eixo_deitado{{1, 0, 0}};
    Ponto p_base_cil_topo_rei{{-3, 38, 0}};
    Cilindro *cil_topo3_rei = new Cilindro(idController->generateNewUID(), p_base_cil_topo_rei, eixo_deitado, 6, 1);
    cil_topo3_rei->setMaterial(*goldMaterialAmb, *goldMaterialDif, *goldMaterialSpec, 1);
    cil_topo3_rei->rotacionar(1, 90);

    Ponto toTranslateRei{{84, 0, -12}};
    con_corpo1_rei->transladar(toTranslateRei);
    cil_base1_rei->transladar(toTranslateRei);
    cil_base2_rei->transladar(toTranslateRei);
    cil_corpo2_rei->transladar(toTranslateRei);
    con_topo1_rei->transladar(toTranslateRei);
    cil_topo2_rei->transladar(toTranslateRei);
    cil_topo3_rei->transladar(toTranslateRei);

    objList.push_back(con_corpo1_rei);
    objList.push_back(cil_base1_rei);
    objList.push_back(cil_base2_rei);
    objList.push_back(cil_corpo2_rei);
    objList.push_back(con_topo1_rei);
    objList.push_back(cil_topo2_rei);
    objList.push_back(cil_topo3_rei);
}

int main(int argc, char **argv)
{
    IDController *idController = new IDController();

    // Montando câmera
    Ponto eye{{30, 70, 90}};
    // Ponto eye{{0, 10, 20}};
    Ponto la{{0, 0, 1}};
    Ponto lu{{0, 100, 0}};
    Camera *cam = new Camera(eye, la, lu);

    vector<Objeto *> objList;

    // Criando cilindro para cluster principal
    Ponto baseCilCluster{{0, -40, 0}};
    Eigen::VectorXd dirCilCluster{{0, 1, 0}};
    // Cluster principal
    Cilindro *cil_para_cluster = new Cilindro(0, baseCilCluster, dirCilCluster, 100, 200);
    Cluster *mainCluster = new Cluster(*cil_para_cluster);

    montarTabuleiro(objList);
    montarPecas(objList);

    // Montando mesa de prata
    Ponto baseMesaPrata{{0, -8, 0}};
    Eigen::VectorXd dirMesaPrata{{0, -1, 0}};
    Cilindro *cil_mesa_prata = new Cilindro(idController->generateNewUID(), baseMesaPrata, dirMesaPrata, 20, 200);
    cil_mesa_prata->setMaterial(*silverAmb, *silverDif, *silverSpec, 89);
    Cilindro *cil_aste_prata = new Cilindro(idController->generateNewUID(), baseMesaPrata, dirMesaPrata, 200, 20);
    cil_aste_prata->setMaterial(*silverAmb, *silverDif, *silverSpec, 89);

    objList.push_back(cil_mesa_prata);
    objList.push_back(cil_aste_prata);

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

    Cenario *cena = new Cenario(*cam, objList, luzList, *mainCluster);

    // Abrindo uma janela com Open GL
    Window w(argc, argv, 800, 600, "CG Study", cena);

    return 0;
}
