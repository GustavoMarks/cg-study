#include "LuzPontual.hpp"

LuzPontual::LuzPontual(RGBIntesity i, Ponto pf) : LuzAmbiente(i)
{
	this->pf = pf;
	this->luzType = 3;
}

Eigen::Vector3d LuzPontual::getLightToPoint(Ponto p)
{
	Ponto Pdifs = this->pf - p;
	Eigen::Vector3d L;
	L << Pdifs.x(), Pdifs.y(), Pdifs.y();
	L.normalize();
	return L;
}

Eigen::VectorXd LuzPontual::getOriginPoint()
{
	Eigen::VectorXd LO{{this->pf.x(), this->pf.y(), this->pf.z()}};
	return LO;
}

void LuzPontual::cameraTransform(Eigen::Matrix4d mwc)
{
	Eigen::Vector4d v;
	v << this->pf.x(), this->pf.y(), this->pf.z(), 1;
	v = mwc * v;
	Ponto updateDf{{v.x(), v.y(), v.z()}};
	this->pf = updateDf;
}