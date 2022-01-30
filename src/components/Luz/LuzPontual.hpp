#include "LuzAmbiente.hpp"

class LuzPontual : public LuzAmbiente
{
private:
	/* data */
public:
	Ponto pf;
	LuzPontual(RGBIntesity i, Ponto pf);
	Eigen::Vector3d getLightToPoint(Ponto p);
};