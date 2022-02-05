#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(RGBIntesity i, Eigen::Vector3d df) : LuzAmbiente(i)
{
	this->df = df;
	this->luzType = 2;
}

Eigen::Vector3d LuzDirecional::getLightToPoint(Ponto p)
{
	return this->df * (-1);
}

Eigen::Vector3d LuzDirecional::getOriginPoint()
{
	return this->df; // "Origin no infino"
}

void LuzDirecional::cameraTransform(Eigen::Matrix4d mwc)
{
	Eigen::Vector4d v;
	v << this->df.x(), this->df.y(), this->df.z(), 1;
	v = mwc * v;
	Eigen::Vector3d updateDf;
	updateDf << v.x(), v.y(), v.z();
	this->df = updateDf;
}