#include "LuzAmbiente.hpp"

class LuzPontual : public LuzAmbiente
{
private:
	/* data */
public:
	Ponto pf;
	LuzPontual(RGBIntesity i, Ponto pf);
	virtual Eigen::Vector3d getLightToPoint(Ponto p);
	Eigen::Vector3d getOriginPoint();
	virtual void cameraTransform(Eigen::Matrix4d mwc);
};