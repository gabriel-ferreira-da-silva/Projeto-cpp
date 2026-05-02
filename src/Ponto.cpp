#include "Ponto.h"
#include "Vetor.h"

// Construtor
Ponto::Ponto(double x, double y, double z) : x(x), y(y), z(z) {}

// Ponto + Vetor = Ponto
Ponto Ponto::operator+(const Vetor& other) const {
    return Ponto(x + other.getX(), 
                 y + other.getY(), 
                 z + other.getZ());
}

// Ponto - Ponto = Vetor
Vetor Ponto::operator-(const Ponto& other) const {
    return Vetor(x - other.x, 
                 y - other.y, 
                 z - other.z);
}

// Ponto - Vetor = Ponto
Ponto Ponto::operator-(const Vetor& other) const {
    return Ponto(x - other.getX(), 
                 y - other.getY(), 
                 z - other.getZ());
}

// Operador de saída (__repr__)
std::ostream& operator<<(std::ostream& os, const Ponto& p) {
    os << "Ponto(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

// Acesso estilo array (opcional)
double Ponto::operator[](int index) const {
    switch(index) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Índice deve ser 0, 1 ou 2");
    }
}