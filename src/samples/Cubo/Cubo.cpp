#include "../samples.hpp"

using namespace std;

Cubo::Cubo(int id, double side)
    : Objeto(id)
{
    Ponto p1{{0, 0, 0}};
    Ponto p2{{side, 0, 0}};
    Ponto p3{{side, 0, side}};
    Ponto p4{{0, 0, side}};
    Ponto p5{{0, side, 0}};
    Ponto p6{{side, side, 0}};
    Ponto p7{{side, side, side}};
    Ponto p8{{0, side, side}};

    vector<FaceTriangular> faces;
    FaceTriangular f1(0, p8, p3, p4);
    FaceTriangular f2(1, p8, p7, p3);
    FaceTriangular f3(2, p7, p2, p6);
    FaceTriangular f4(3, p3, p2, p7);
    FaceTriangular f5(4, p2, p1, p6);
    FaceTriangular f6(5, p6, p1, p5);
    FaceTriangular f7(6, p5, p1, p4);
    FaceTriangular f8(7, p5, p4, p8);
    FaceTriangular f9(8, p5, p7, p8);
    FaceTriangular f10(9, p5, p6, p7);
    FaceTriangular f11(10, p2, p3, p4);
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