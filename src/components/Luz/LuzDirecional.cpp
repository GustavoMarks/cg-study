#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(RGBIntesity i, Eigen::Vector3d df) : LuzAmbiente(i)
{
	this->df = df;
}