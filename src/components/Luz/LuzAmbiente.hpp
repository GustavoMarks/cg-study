#include "../../helpers/RGBIntensity/RGBIntensity.hpp"
#include <eigen-3.4.0/Eigen/Dense>
#include "../Ponto.hpp"

class LuzAmbiente
{
public:
	RGBIntesity i;
	LuzAmbiente(RGBIntesity i);
	Eigen::Vector3d getLightToPoint(Ponto p); // Sobreescrever em classes derivadas
};