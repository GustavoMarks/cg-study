class FaceTriangular : public Objeto
{
private:
public:
	// Objeto formato por três pontos (ordenados em sentido anti-horário)
	FaceTriangular(int id);
	FaceTriangular(int id, Ponto p1, Ponto p2, Ponto p3);

	bool hitRay(VectorXd p0, VectorXd d, float &t_min);
	bool hitLight(Ponto colisedPointView, VectorXd p0Light, VectorXd dLight, Eigen::Vector3d &n);
};