#include "LuzAmbiente.hpp"

LuzAmbiente::LuzAmbiente(RGBIntesity i)
{
	this->i = i;
}

Eigen::Vector3d LuzAmbiente::getLightToPoint(Ponto p)
{
	return Eigen::Vector3d{{0, 0, 0}};
}

Eigen::VectorXd LuzAmbiente::getOriginPoint()
{
	Eigen::VectorXd nullVector;
	nullVector << 0, 0, 0;
	return nullVector;
}

Eigen::VectorXd LuzAmbiente::getDir()
{
	Eigen::VectorXd nullVector;
	nullVector << 0, 0, 0;
	return nullVector;
}

void LuzAmbiente::cameraTransform(Eigen::Matrix4d mwc)
{
}