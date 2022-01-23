#include "../../components/Ponto.hpp"

class CurvaBezier : public Malha
{
private:
	double b_1(double t);
	double b_2(double t);
	double b_3(double t);
	double b_4(double t);

public:
	int num_paralelos;
	int num_meridianos;
	CurvaBezier(int num_paralelos, int num_meridianos, Ponto p0, Ponto p1, Ponto p2, Ponto p3, int id);
};