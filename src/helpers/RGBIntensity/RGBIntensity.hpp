class RGBIntesity
{
public:
	double r, b, g;
	RGBIntesity();
	RGBIntesity(double r, double g, double b);
	RGBIntesity cross(RGBIntesity b);
	RGBIntesity sum(RGBIntesity b);
	RGBIntesity atenuar(float fator);
};