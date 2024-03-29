#include "../samples.hpp"

using namespace std;

Cubo::Cubo(int id, float width, float height, float depth)
    : Objeto(id)
{
    // Montando um cubo na origem do sistema
    Ponto p1{{0, 0, 0}};
    Ponto p2{{width, 0, 0}};
    Ponto p3{{width, 0, depth}};
    Ponto p4{{0, 0, depth}};
    Ponto p5{{0, height, 0}};
    Ponto p6{{width, height, 0}};
    Ponto p7{{width, height, depth}};
    Ponto p8{{0, height, depth}};

    vector<FaceTriangular> faces;
    // Faces traseiras
    FaceTriangular f1(0, p1, p5, p2);
    FaceTriangular f2(1, p2, p5, p6);
    // Faces lateral esquerda
    FaceTriangular f3(2, p5, p1, p4);
    FaceTriangular f4(3, p5, p4, p8);
    // Faces frontais
    FaceTriangular f5(4, p8, p4, p3);
    FaceTriangular f6(5, p8, p3, p7);
    // Faces lateral direita
    FaceTriangular f7(6, p7, p3, p2);
    FaceTriangular f8(7, p7, p2, p6);
    // Faces topo
    FaceTriangular f9(8, p7, p6, p5);
    FaceTriangular f10(9, p7, p5, p8);
    // Faces base
    FaceTriangular f11(10, p3, p4, p2);
    FaceTriangular f12(11, p4, p1, p2);

    faces.push_back(f1);
    faces.push_back(f2);
    faces.push_back(f3);
    faces.push_back(f4);
    faces.push_back(f5);
    faces.push_back(f6);
    faces.push_back(f7);
    faces.push_back(f8);
    faces.push_back(f9);
    faces.push_back(f10);
    faces.push_back(f11);
    faces.push_back(f12);

    this->faces = faces;
}

void Cubo::transladar(Ponto t)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).transladar(t);
    }
}

void Cubo::rotacionar(int plan, double ang)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).rotacionar(plan, ang);
    }
}

void Cubo::rotacionar(Ponto P1, Ponto P2, double ang)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).rotacionar(P1, P2, ang);
    }
}

void Cubo::escalar(double sx, double sy, double sz)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).escalar(sx, sy, sz);
    }
}

void Cubo::cisalhar(double ang_onX_planXYZ)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).cisalhar(ang_onX_planXYZ);
    }
}

void Cubo::refletir(int plan)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).refletir(plan);
    }
}

void Cubo::refletir(Ponto A, Ponto B, Ponto C)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).refletir(A, B, C);
    }
}

bool Cubo::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
    bool result = false;
    float aux = 100000000000000;
    for (int i = 0; i < this->faces.size(); i++)
    {
        bool localResult = this->faces.at(i).hitRay(p0, d, t_min);
        if (localResult)
        {
            result = localResult;
            if (aux < t_min)
                t_min = aux;
            else
                aux = t_min;
        }
    }

    return result;
}

bool Cubo::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
    bool result = false;
    for (int i = 0; i < this->faces.size(); i++)
    {
        bool localResult = this->faces.at(i).hitLight(colisedPointView, p0Light, dLight, n);
        if (localResult)
            result = localResult;
    }

    return result;
}

void Cubo::cameraTransform(Eigen::Matrix4d mwc)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).cameraTransform(mwc);
    }
}