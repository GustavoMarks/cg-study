#include "Malha.hpp"
#include <iostream>
#include <stack>

using namespace std;

Malha::Malha(int id, std::vector<Face> faces) : Objeto(id)
{
	this->faces = faces;
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

	this->pontos = pointsList;
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
	newFaces.reserve(this->faces.size());

	int i;
	for (i = 2; i < newPoints.size(); i += 3)
	{
		Ponto p2 = newPoints.at(i);
		Ponto p1 = newPoints.at(i - 1);
		Ponto p0 = newPoints.at(i - 2);

		Aresta a0 = make_pair(p0, p1);
		Aresta a1 = make_pair(p1, p2);
		Aresta a2 = make_pair(p2, p0);

		// TODO: verificar ordenação em sentido anti-horário
		Face nexFace = make_tuple(a1, a2, a0);
		newFaces.push_back(nexFace);
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
	// this->updateStruct(this->pontos);
	int num_faces = (int)this->faces.size();
	float a, f, u, v;
	Eigen::Vector3d h, s, q, p03d, d3d;
	p03d << p0.x(), p0.y(), p0.z();
	d3d << d.x(), d.y(), d.z();
	std::vector<float> intersecoes;

	for (int i = 0; i < num_faces; i++)
	{
		// TODO: Ver questão dos vertices em sentido anti-horário

		// Obtendo os vertices da face
		Aresta a0 = std::get<0>(this->faces[i]);
		Aresta a1 = std::get<1>(this->faces[i]);
		// Aresta a2 = std::get<2>(this->faces[i]);
		Ponto v0 = std::get<0>(a0);
		Ponto v1 = std::get<1>(a0);
		Ponto v2;

		if (std::get<0>(a1) != v0 && std::get<0>(a1) != v1)
		{
			v2 = std::get<0>(a1);
		}
		else
		{
			v2 = std::get<1>(a1);
		}

		Eigen::Vector3d v03d;
		v03d << v0.x(), v0.y(), v0.z();
		Eigen::Vector3d v13d;
		v13d << v1.x(), v1.y(), v1.z();
		Eigen::Vector3d v23d;
		v23d << v2.x(), v2.y(), v2.z();

		Eigen::Vector3d aresta1 = v13d - v03d;
		Eigen::Vector3d aresta2 = v23d - v03d;
		h = d3d.cross(aresta2);
		a = aresta1.dot(h);

		float episilon = 0.0001;

		if (a < episilon || std::abs(a) < episilon)
			continue;

		f = 1.0f / a;
		s = p03d - v0;
		u = f * s.dot(h);
		if (u < 0.0 || u > 1.0)
			continue;

		q = s.cross(aresta1);
		v = f * d3d.dot(q);
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

void Malha::cameraTransform(Eigen::Matrix4d mwc)
{
	this->pontos = this->getStruct();
	cout << this->pontos.at(0) << endl;
	Objeto::cameraTransform(mwc);
	this->updateStruct(this->pontos);
	cout << this->pontos.at(0) << endl;
}