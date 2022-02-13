#include "../samples.hpp"
#include <vector>

using namespace std;
#define PI 3.14159265

double CurvaBezier::b_1(double t)
{
	return (1.0 - t - t * t + t * t * t);
}

double CurvaBezier::b_2(double t)
{
	return (t - 2.0 * t * t + t * t * t);
}

double CurvaBezier::b_3(double t)
{
	return (t * t - t * t * t);
}

double CurvaBezier::b_4(double t)
{
	return (2.0 * t * t - t * t * t);
}

CurvaBezier::CurvaBezier(int num_paralelos, int num_meridianos, Ponto p0, Ponto p1, Ponto p2, Ponto p3, int id)
		: Objeto(id)
{
	// preenchendo os vertices
	vector<Ponto> vertices;
	for (int j = 0; j <= num_paralelos; j++)
	{
		// t is the parameter in the range from 0 to 1 to mark the points
		double t = (1.0 / num_paralelos) * j;
		double z = p0[1] * b_1(t) + p1[1] * b_2(t) + p2[1] * b_3(t) + p3[1] * b_4(t);

		for (int i = 0; i <= num_meridianos; i++)
		{
			double r = p0[0] * b_1(t) + p1[0] * b_2(t) + p2[0] * b_3(t) + p3[0] * b_4(t);

			// Coordinates x, y, z of the vertices defined when a parallel
			// circle crosses a meridian profile curve.
			double x = r * cos((2.0 * PI / num_meridianos) * (float)i);
			double y = r * sin((2.0 * PI / num_meridianos) * (float)i);
			Ponto p{{x, y, z}};

			vertices.push_back(p);
		}
	}

	// preenchendo as faces com arestas no sentido anti-horario
	vector<FaceTriangular> faces;
	int idFace = 0;
	// cada quadrado tem duas faces triangulares
	for (int i = 0; i < num_paralelos; i++)
	{
		for (int j = (num_meridianos + 1) * i; j < (num_meridianos + 1) * i + num_meridianos; j++)
		{
			Ponto p_esq_inf = vertices[j];
			Ponto p_dir_inf = vertices[j + 1];
			Ponto p_esq_sup = vertices[j + num_meridianos + 1];
			Ponto p_dir_sup = vertices[j + num_meridianos + 2];

			// face triagular inferior
			FaceTriangular f_inf(idFace, p_esq_inf, p_dir_inf, p_esq_sup);
			idFace++;
			// face triagular superior
			FaceTriangular f_sup(idFace, p_esq_sup, p_dir_inf, p_dir_sup);
			idFace++;

			faces.push_back(f_inf);
			faces.push_back(f_sup);
		}
	}

	this->faces = faces;
}

void CurvaBezier::transladar(Ponto t)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).transladar(t);
    }
}

void CurvaBezier::rotacionar(int plan, double ang)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).rotacionar(plan, ang);
    }
}

void CurvaBezier::rotacionar(Ponto P1, Ponto P2, double ang)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).rotacionar(P1, P2, ang);
    }
}

void CurvaBezier::escalar(double sx, double sy, double sz)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).escalar(sx, sy, sz);
    }
}

void CurvaBezier::cisalhar(double ang_onX_planXYZ)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).cisalhar(ang_onX_planXYZ);
    }
}

void CurvaBezier::refletir(int plan)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).refletir(plan);
    }
}

void CurvaBezier::refletir(Ponto A, Ponto B, Ponto C)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).refletir(A, B, C);
    }
}

bool CurvaBezier::hitRay(VectorXd p0, VectorXd d, float &t_min)
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

bool CurvaBezier::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
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

void CurvaBezier::cameraTransform(Eigen::Matrix4d mwc)
{
    for (int i = 0; i < this->faces.size(); i++)
    {
        this->faces.at(i).cameraTransform(mwc);
    }
}