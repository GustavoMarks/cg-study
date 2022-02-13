#include "../../components/Ponto.hpp"

class CurvaBezier : public Objeto
{
private:
	double b_1(double t);
	double b_2(double t);
	double b_3(double t);
	double b_4(double t);

public:
	vector<FaceTriangular> faces;

	int num_paralelos;
	int num_meridianos;
	CurvaBezier(int num_paralelos, int num_meridianos, Ponto p0, Ponto p1, Ponto p2, Ponto p3, int id);

	void transladar(Ponto t);
	void rotacionar(int plan, double ang);
	void rotacionar(Ponto P1, Ponto P2, double ang);
	void escalar(double sx, double sy, double sz);
	void cisalhar(double ang_onX_planXYZ);
	void refletir(int plan);
	void refletir(Ponto A, Ponto B, Ponto C);
	bool hitRay(VectorXd p0, VectorXd d, float &t_min);
	bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
	void cameraTransform(Eigen::Matrix4d mwc);
};