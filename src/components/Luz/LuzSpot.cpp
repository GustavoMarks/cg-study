#include "LuzSpot.hpp"
#include <math.h>

#define PI 3.14159265

LuzSpot::LuzSpot(RGBIntesity i, Ponto pf, Eigen::Vector3d df, double ang) : LuzPontual(i, pf)
{
	this->ang = ang;
	this->df = df;
}

Eigen::Vector3d LuzSpot::getLightToPoint(Ponto p)
{
	// Calculando cosseno do angulo entre o vetor df e o vetor p~pf
	Ponto Pdifs = this->pf - p;
	Eigen::Vector3d L;
	L << Pdifs.x(), Pdifs.y(), Pdifs.y();
	L = L / L.norm();

	Eigen::Vector3d l;
	l = (1) * L;

	double cosAlf;

	cosAlf = l.dot(this->df) / l.norm() * this->df.norm();
	if (cosAlf > cos(this->ang * PI / 180.0))
	{
		return L * 0;
	}
	return L * cosAlf;
}