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
	return RGBIntesity(this->r * b.r, this->g * b.g, this->b * b.b);
}