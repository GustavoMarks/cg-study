class Cubo : public Objeto
{
private:
public:
    double side;
    vector<FaceTriangular> faces;
    Cubo(int id, float width, float height, float depth);

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