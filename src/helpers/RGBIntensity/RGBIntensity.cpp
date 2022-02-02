#include "RGBIntensity.hpp"

RGBIntesity::RGBIntesity()
{
	this->r = 0;
	this->b = 0;
	this->g = 0;
}

RGBIntesity::RGBIntesity(double r, double b, double g)
{
	this->r = r > 1 ? 1 : r;
	this->b = b > 1 ? 1 : b;
	this->g = g > 1 ? 1 : g;
}

RGBIntesity RGBIntesity::cross(RGBIntesity b)
{
	double rResult = this->r * b.r < 1 ? this->r * b.r : 1;
	double gResult = this->g * b.g < 1 ? this->g * b.g : 1;
	double bResult = this->b * b.b < 1 ? this->b * b.b : 1;
	return RGBIntesity(rResult, gResult, bResult);
}

RGBIntesity RGBIntesity::sum(RGBIntesity b)
{
	double rResult = this->r + b.r < 1 ? this->r + b.r : 1;
	double gResult = this->g + b.g < 1 ? this->g + b.g : 1;
	double bResult = this->b + b.b < 1 ? this->b + b.b : 1;
	return RGBIntesity(rResult, gResult, bResult);
}