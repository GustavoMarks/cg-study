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

	Eigen::Vector3d normal_3d;
	normal_3d = v1.cross(v2);
	normal_3d.normalize();

	// Criando plano da face para calcular interseção
	Eigen::VectorXd normal{{normal_3d.x(), normal_3d.y(), normal_3d.z()}};
	Plano planoFace(0, p1, normal);

	// Verificando se raio atinge face
	bool hitPlan = planoFace.hitRay(p0, d, t_min);

	if (!hitPlan)
		return false;

	// Usando coordenadas baricentricas para verificar se ponto de interseção está dentro da face
	Ponto colisedPoint = p0 + (t_min * d);
	Eigen::Vector3d colised_3d;
	colised_3d << colisedPoint.x(), colisedPoint.y(), colisedPoint.z();

	Eigen::Vector3d a_ks = (p1_3d - colised_3d).cross(p2_3d - colised_3d);
	a_ks.normalize();
	if (a_ks.dot(normal_3d) < 0)
		return false;

	Eigen::Vector3d a_eta = (p2_3d - colised_3d).cross(p3_3d - colised_3d);
	a_eta.normalize();
	if (a_eta.dot(normal_3d) < 0)
		return false;

	Eigen::Vector3d a_zeta = (p3_3d - colised_3d).cross(p1_3d - colised_3d);
	a_zeta.normalize();
	if (a_zeta.dot(normal_3d) < 0)
		return false;

	// double ks = a_ks.norm();
	// double eta = a_eta.norm();
	// double zeta = 1 - eta - ks;
	// if (zeta < 0)
	// {
	// 	false;
	// }

	return true;
}

bool FaceTriangular::hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n)
{
	float t_min_light;
	bool resultHit = this->hitRay(p0Light, dLight, t_min_light);

	if (resultHit)
	{
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
		v1 = p1_3d - p2_3d;
		Eigen::Vector3d v2;
		v2 = p1_3d - p3_3d;

		n = v1.cross(v2);
		n.normalize();

		return true;
	}

	return false;
}

void FaceTriangular::cameraTransform(Eigen::Matrix4d mwc){

};