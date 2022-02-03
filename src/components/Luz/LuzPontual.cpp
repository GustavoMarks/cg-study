#include "LuzPontual.hpp"

LuzPontual::LuzPontual(RGBIntesity i, Ponto pf) : LuzAmbiente(i)
{
	this->pf = pf;
	this->isAmbiente = false;
}

Eigen::Vector3d LuzPontual::getLightToPoint(Ponto p)
{
	Ponto Pdifs = this->pf - p;
	Eigen::Vector3d L;
	L << Pdifs.x(), Pdifs.y(), Pdifs.y();
	L.normalize();
	return L;
}

Eigen::Vector3d LuzPontual::getOriginPoint(){
	Eigen::Vector3d LO;
	LO << this->pf.x(), this->pf.y(), this->pf.z();
	return LO;
}