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

void Malha::transladar(Ponto p){
	this->pontos = this->getStruct();
	Objeto::transladar(p);
	this->updateStruct(this->pontos);
}

void Malha::rotacionar(double aroundX_ang, double aroundY_ang, double aroundZ_ang){
	this->pontos = this->getStruct();
	Objeto::rotacionar(aroundX_ang, aroundY_ang, aroundZ_ang);
	this->updateStruct(this->pontos);
}

void Malha::escalar(double sx, double sy, double sz){
	this->pontos = this->getStruct();
	Objeto::escalar(sx, sy, sz);
	this->updateStruct(this->pontos);
}