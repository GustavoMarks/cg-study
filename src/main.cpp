#include "./components/Objeto/Objeto.hpp"
#include <iostream>

int main() {
    Ponto p1 {{1.0, 1.0, 1.0}};
    Ponto p2 {{2.0, 2.0, 2.0}};
    Ponto p3 {{3.0, 3.0, 3.0}};
    Ponto p4 {{4.0, 4.0, 4.0}};

    std::cout << p1 << std::endl;
    return 0;
}