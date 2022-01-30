#include "LuzPontual.hpp"

LuzPontual::LuzPontual(RGBIntesity i, Ponto pf) : LuzAmbiente(i)
{
	this->pf = pf;
}

Eigen::Vector3d LuzPontual::getLightToPoint(Ponto p)
{
	Ponto Pdifs = this->pf - p;
	Eigen::Vector3d L;
	L << Pdifs.x(), Pdifs.y(), Pdifs.y();
	L = L / L.norm();
	return L;
}