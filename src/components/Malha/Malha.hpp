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
	void rotacionar(double aroundX_ang, double aroundY_ang, double aroundZ_ang);
	void escalar(double sx, double sy, double sz);
};