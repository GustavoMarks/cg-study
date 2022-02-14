#include "../../components/Cluster/Cluster.hpp"
#include <eigen-3.4.0/Eigen/Dense>

class LuzAmbiente
{
public:
	Eigen::Vector3d df;
	double ang;
	RGBIntesity i;
	int luzType = 1;
	LuzAmbiente(RGBIntesity i);
	virtual Eigen::Vector3d getLightToPoint(Ponto p); // Sobreescrever em classes derivadas
	virtual Eigen::VectorXd getOriginPoint();
	virtual Eigen::VectorXd getDir();
	virtual void cameraTransform(Eigen::Matrix4d mwc);
};