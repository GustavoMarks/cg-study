#include "LuzPontual.hpp"

class LuzSpot : public LuzPontual
{
public:
	Eigen::Vector3d df;
	double ang;
	LuzSpot(RGBIntesity i, Ponto pf, Eigen::Vector3d df, double ang);
	Eigen::Vector3d getLightToPoint(Ponto p);
};