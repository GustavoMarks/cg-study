class Plano : public Objeto
{
private:
  /* data */
public:
  Ponto p0; // um ponto específico (conhecido) do plano;
  VectorXd n; // é o vetor unitário perpendicular ao plano;
  Plano(int id);
  Plano(int id, Ponto p0, VectorXd n);
  bool hitRay(VectorXd p0, VectorXd d, float &t_int);
};