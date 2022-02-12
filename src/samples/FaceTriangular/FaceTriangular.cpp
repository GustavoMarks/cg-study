#include "../samples.hpp"
#include <iostream>

FaceTriangular::FaceTriangular(int id) : Objeto(id)
{
}

FaceTriangular::FaceTriangular(int id, Ponto p1, Ponto p2, Ponto p3) : Objeto(id)
{
	std::vector<Ponto> pontos;
	pontos.push_back(p1);
	pontos.push_back(p2);
	pontos.push_back(p3);

	this->pontos = pontos;
}

bool FaceTriangular::hitRay(VectorXd p0, VectorXd d, float &t_min)
{
	// Utilizando algoritmo de Möller–Trumbore
	const float EPSILON = 0.0000001;
	Ponto p1 = this->pontos.at(0);
	Ponto p2 = this->pontos.at(1);
	Ponto p3 = this->pontos.at(2);

	Eigen::Vector3d origenRay;
	origenRay << p0.x(), p0.y(), p0.z();

	Eigen::Vector3d p1_3d;
	p1_3d << p1.x(), p1.y(), p1.z();

	Eigen::Vector3d p2_3d;
	p2_3d << p2.x(), p2.y(), p2.z();

	Eigen::Vector3d p3_3d;
	p3_3d << p3.x(), p3.y(), p3.z();

	Eigen::Vector3d v1;
	v1 = p2_3d - p1_3d;
	Eigen::Vector3d v2;
	v2 = p3_3d - p1_3d;

	Eigen::Vector3d rayDir;
	rayDir << d.x(), d.y(), d.z();

	Eigen::Vector3d h = rayDir.cross(v2);
	float a = v1.dot(h);

	if (a > -EPSILON && a < EPSILON)
		return false; // Raio é paralelo ao triângulo

	float f = 1.0 / a;
	Eigen::Vector3d s = origenRay - p1_3d;
	float u = f * s.dot(h);
	if (u < 0.0 || u > 1.0)
		return false;

	Eigen::Vector3d q = s.cross(v1);
	float v = f * rayDir.dot(q);
	if (v < 0.0 || u + v > 1.0)
		return false;

	// Calculando t_min
	t_min = f * v2.dot(q);
	if (t_min > EPSILON)
		return true;

	return false;
}

bool FaceTriangular::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
	float t_min_light;
	bool resultHit = this->hitRay(p0Light, dLight, t_min_light);

	if (resultHit)
	{
		// Calculando ponto de interseção entre luz e objeto
		Eigen::VectorXd colisedPoint;
		colisedPoint = p0Light + (t_min_light * dLight);
		Eigen::VectorXd cpvXd{{colisedPointView.x(), colisedPointView.y(), colisedPointView.z()}};

		if (!colisedPoint.isApprox(cpvXd, 0.001))
		{
			return false;
		}

		// Obtendo normal
		// Buscando a normal da face
		Ponto p1 = this->pontos.at(0);
		Ponto p2 = this->pontos.at(1);
		Ponto p3 = this->pontos.at(2);

		Eigen::Vector3d p1_3d;
		p1_3d << p1.x(), p1.y(), p1.z();

		Eigen::Vector3d p2_3d;
		p2_3d << p2.x(), p2.y(), p2.z();

		Eigen::Vector3d p3_3d;
		p3_3d << p3.x(), p3.y(), p3.z();

		Eigen::Vector3d v1;
		v1 = p2_3d - p1_3d;
		Eigen::Vector3d v2;
		v2 = p3_3d - p1_3d;

		n = v1.cross(v2);
		n.normalize();

		return true;
	}

	return false;
}