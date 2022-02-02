class RGBIntesity
{
public:
	double r, b, g;
	RGBIntesity();
	RGBIntesity(double r, double b, double g);
	RGBIntesity cross(RGBIntesity b);
	RGBIntesity sum(RGBIntesity b);
};