#include "LuzSpot.hpp"

LuzSpot::LuzSpot(RGBIntesity i, Ponto pf, Eigen::Vector3d df, double ang) : LuzPontual(i, pf)
{
	this->ang = ang;
	this->df = df;
}