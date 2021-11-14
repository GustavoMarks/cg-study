// Classe para controlar IDs únicos para Objetos
// Cada geração de ID de uma certa instância gera um novo ID

class IDController {
    private:
        int nextGlobalId;

    public:
        IDController();
        int generateNewUID();
};