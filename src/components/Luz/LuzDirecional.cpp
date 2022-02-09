#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(RGBIntesity i, Eigen::Vector3d df) : LuzAmbiente(i)
{
	df.normalize();
	this->df = df;
	this->luzType = 2;
}

Eigen::Vector3d LuzDirecional::getLightToPoint(Ponto p)
{
	return this->df * (-1);
}

Eigen::VectorXd LuzDirecional::getOriginPoint()
{
	Eigen::VectorXd returnedDir{{this->df.x(), this->df.y(), this->df.z()}};
	return returnedDir * 1000; // Origin no "infino"
}

Eigen::VectorXd LuzDirecional::getDir()
{
	Eigen::VectorXd convertedDr{{this->df.x(), this->df.y(), this->df.z()}};
	return convertedDr;
}