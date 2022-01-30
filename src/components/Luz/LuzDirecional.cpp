#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(RGBIntesity i, Eigen::Vector3d df) : LuzAmbiente(i)
{
	this->df = df;
}

Eigen::Vector3d LuzDirecional::getLightToPoint(Ponto p)
{
	return this->df * (-1);
}