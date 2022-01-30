#include "LuzAmbiente.hpp"

LuzAmbiente::LuzAmbiente(RGBIntesity i)
{
	this->i = i;
}

Eigen::Vector3d LuzAmbiente::getLightToPoint(Ponto p)
{
	return Eigen::Vector3d{{0, 0, 0}};
}