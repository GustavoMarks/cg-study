#include "Malha.hpp"
#include <iostream>
#include <stack>

using namespace std;

Malha::Malha(int id, std::vector<Face> faces) : Objeto(id)
{
	this->faces = faces;
}

Malha::Malha(int id) : Objeto(id)
{
	this->id = id;
}

std::ostream &operator<<(std::ostream &os, Malha &obj)
{
	os << "Objeto id = " << obj.id << endl;
	os << "-Faces: " << endl;

	int i = 0;
	for (auto it = obj.faces.begin(); it != obj.faces.end(); it++, i++)
	{
		Aresta a0 = get<0>(*it);
		Ponto p0_a0 = get<0>(a0);
		Ponto p1_a0 = get<1>(a0);

		Aresta a1 = get<1>(*it);
		Ponto p0_a1 = get<0>(a1);
		Ponto p1_a1 = get<1>(a1);

		Aresta a2 = get<2>(*it);
		Ponto p0_a2 = get<0>(a2);
		Ponto p1_a2 = get<1>(a2);

		os << "--------------------" << endl;
		os << "--Face " << i << ": " << endl;

		os << "---Aresta 1: " << endl;
		os << "----Vertice 1: " << endl
			 << p0_a0 << endl;
		os << "----Vertice 2: " << endl
			 << p1_a0 << endl;

		os << "---Aresta 2: " << endl;
		os << "----Vertice 1: " << endl
			 << p0_a1 << endl;
		os << "----Vertice 2: " << endl
			 << p0_a1 << endl;

		os << "---Aresta 3: " << endl;
		os << "----Vertice 1: " << endl
			 << p0_a2 << endl;
		os << "----Vertice 2: " << endl
			 << p0_a2 << endl;
	}

	return os;
}

vector<Ponto> Malha::getStruct()
{
	vector<Ponto> pointsList;
	pointsList.reserve(this->faces.size() * 3);

	int i;
	for (i = 0; i < this->faces.size(); i++)
	{
		Face f = this->faces.at(i);
		Aresta &a0 = get<0>(f);
		Ponto p0_a0 = get<0>(a0);
		pointsList.push_back(p0_a0);

		Ponto p1_a0 = get<1>(a0);
		pointsList.push_back(p1_a0);

		Aresta &a1 = get<1>(f);
		Ponto p0_a1 = get<0>(a1);
		Ponto p1_a1 = get<1>(a1);

		if (p0_a0 == p0_a1)
		{
			pointsList.push_back(p1_a1);
		}
		else
		{
			pointsList.push_back(p0_a1);
		}
	}

	return pointsList;
}

void Malha::updateStruct(vector<Ponto> newPoints)
{
	vector<Face> newFaces;

	stack<Ponto> visitedPoints;
	int i;
	for (i = 0; i < newPoints.size(); i++)
	{
		Ponto p = newPoints.at(i);
		if (visitedPoints.size() != 3)
		{
			visitedPoints.push(p);
		}
		else
		{
			Ponto p2 = visitedPoints.top();
			visitedPoints.pop();
			Ponto p1 = visitedPoints.top();
			visitedPoints.pop();
			Ponto p0 = visitedPoints.top();
			visitedPoints.pop();

			Aresta a0 = make_pair(p0, p1);
			Aresta a1 = make_pair(p1, p2);
			Aresta a2 = make_pair(p2, p0);

			// TODO: verificar ordenação em sentido anti-horário
			Face nexFace = make_tuple(a1, a2, a0);
			newFaces.push_back(nexFace);
		}
	}

	this->faces = newFaces;
}

// Cria uma nova malha unindo malhas
void Malha::concat(Malha malha)
{
	vector<Face> newFaces = malha.faces;
	faces.insert(faces.end(), newFaces.begin(), newFaces.end());
}

void Malha::transladar(Ponto p)
{
	this->pontos = this->getStruct();
	Objeto::transladar(p);
	this->updateStruct(this->pontos);
}

void Malha::rotacionar(int axis, double ang)
{
	this->pontos = this->getStruct();
	Objeto::rotacionar(axis, ang);
	this->updateStruct(this->pontos);
}

void Malha::rotacionar(Ponto P1, Ponto P2, double ang)
{
	this->pontos = this->getStruct();
	Objeto::rotacionar(P1, P2, ang);
	this->updateStruct(this->pontos);
}

void Malha::escalar(double sx, double sy, double sz)
{
	this->pontos = this->getStruct();
	Objeto::escalar(sx, sy, sz);
	this->updateStruct(this->pontos);
}

void Malha::cisalhar(double ang_onX_planXYZ)
{
	this->pontos = this->getStruct();
	Objeto::cisalhar(ang_onX_planXYZ);
	this->updateStruct(this->pontos);
}

void Malha::refletir(int plan)
{
	this->pontos = this->getStruct();
	Objeto::refletir(plan);
	this->updateStruct(this->pontos);
}

void Malha::refletir(Ponto A, Ponto B, Ponto C)
{
	this->pontos = this->getStruct();
	Objeto::refletir(A, B, C);
	this->updateStruct(this->pontos);
}

bool Malha::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
	int num_faces = (int)this->faces.size();
	float a, f, u, v;
	VectorXd h, s, q;
	std::vector<float> intersecoes;

	for (int i = 0; i < num_faces; i++)
	{
		// TODO: Ver questão dos vertices em sentido anti-horário

		cout << "Método filho chamado..." << endl;

		// Obtendo os vertices da face
		Aresta a0 = std::get<0>(this->faces[i]);
		Aresta a1 = std::get<1>(this->faces[i]);
		// Aresta a2 = std::get<2>(this->faces[i]);
		Ponto v0 = std::get<0>(a0);
		Ponto v1 = std::get<1>(a0);
		Ponto v2;
		if (std::get<0>(a1) != v0)
		{
			v2 = std::get<0>(a1);
		}
		else
		{
			v2 = std::get<1>(a1);
		}

		VectorXd aresta1 = v1 - v0;
		VectorXd aresta2 = v2 - v0;
		h = d * aresta2;
		a = aresta1.dot(h);

		float episilon = 0.0001;

		if (a < episilon || std::abs(a) < episilon)
			continue;

		f = 1.0f / a;
		s = p0 - v0;
		u = f * s.dot(h);
		if (u < 0.0 || u > 1.0)
			continue;

		q = s * aresta1;
		v = f * d.dot(q);
		if (v < 0.0 || u + v > 1.0)
			continue;

		float t_int = f * aresta2.dot(q);
		intersecoes.push_back(t_int);
	}

	int num_intersecoes = (int)intersecoes.size();
	if (num_intersecoes == 0)
		return false;

	t_min = intersecoes[0];
	for (int i = 1; i < num_intersecoes; i++)
		if (intersecoes[i] < t_min)
			t_min = intersecoes[i];

	return true;
}
