#include <ostream>
#include <vector>
#include "../Face.hpp"
#include "../Objeto/Objeto.hpp"

class Malha : public Objeto
{
private:
	// Sobrescrevendo para conversão de faces para lista de pontos
  std::vector<Ponto> getStruct();
  void updateStruct(std::vector<Ponto>);
public:
	Malha(int id, std::vector<Face> faces);
	Malha(int id);
	std::vector<Face> faces;
	friend std::ostream &operator<<(std::ostream &os, Objeto &obj);
	void concat(Malha malha);

	// Sobreescrevendo funções para atualização da estrutura de pontos para face
	void transladar(Ponto t);
	void rotacionar(int axis, double ang);
	void rotacionar(Ponto P1, Ponto P2, double ang);
	void escalar(double sx, double sy, double sz);
	void cisalhar(double ang_onX_planXYZ);
	void refletir(int plan);
	void refletir(Ponto A, Ponto B, Ponto C);

	// Sobrescrevendo função que calcula interseção de um raio com faces da malha
  virtual bool hitRay(VectorXd p0, VectorXd d, float &t_min, Eigen::Vector3d &n);
	void cameraTransform(Eigen::Matrix4d mwc);
};