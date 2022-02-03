#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(RGBIntesity i, Eigen::Vector3d df) : LuzAmbiente(i)
{
	this->df = df;
	this->isAmbiente = false;
}

Eigen::Vector3d LuzDirecional::getLightToPoint(Ponto p)
{
	return this->df * (-1);
}

Eigen::Vector3d LuzDirecional::getOriginPoint(){
	return this->df; // "Origin no infino"
}