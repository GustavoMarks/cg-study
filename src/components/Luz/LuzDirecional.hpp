#include "LuzSpot.hpp"

class LuzDirecional : public LuzAmbiente
{
public:
	Eigen::Vector3d df;
	LuzDirecional(RGBIntesity i, Eigen::Vector3d df);
	Eigen::Vector3d getLightToPoint(Ponto p);
	Eigen::VectorXd getOriginPoint();
	Eigen::VectorXd getDir();
};