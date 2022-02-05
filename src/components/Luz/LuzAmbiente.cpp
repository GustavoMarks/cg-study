#include "LuzAmbiente.hpp"

LuzAmbiente::LuzAmbiente(RGBIntesity i)
{
	this->i = i;
}

Eigen::Vector3d LuzAmbiente::getLightToPoint(Ponto p)
{
	return Eigen::Vector3d{{0, 0, 0}};
}

Eigen::Vector3d LuzAmbiente::getOriginPoint()
{
	return Eigen::Vector3d{{0, 0, 0}};
}

void LuzAmbiente::cameraTransform(Eigen::Matrix4d mwc)
{
}