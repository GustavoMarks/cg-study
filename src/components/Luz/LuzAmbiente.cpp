#include "LuzAmbiente.hpp"

LuzAmbiente::LuzAmbiente(RGBIntesity i)
{
	this->i = i;
}

Eigen::Vector3d LuzAmbiente::getLightToPoint(Ponto p)
{
	Eigen::Vector3d oLight;
	oLight << 0, 0, 0;
	return oLight;
}

Eigen::VectorXd LuzAmbiente::getOriginPoint()
{
	Eigen::VectorXd nullVector{{0, 0, 0}};
	return nullVector;
}

Eigen::VectorXd LuzAmbiente::getDir()
{
	Eigen::VectorXd nullVector{{0, 0, 0}};
	return nullVector;
}

void LuzAmbiente::cameraTransform(Eigen::Matrix4d mwc)
{
}