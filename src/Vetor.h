#ifndef VETOR_H
#define VETOR_H

#include <iostream>
#include <cmath>

class Vetor {
public:
    // Construtor
    Vetor(double x = 0.0, double y = 0.0, double z = 0.0);
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    // Setters
    void setX(double val) { x = val; }
    void setY(double val) { y = val; }
    void setZ(double val) { z = val; }
    
    // Operações vetoriais
    Vetor operator+(const Vetor& other) const;
    Vetor operator-(const Vetor& other) const;
    Vetor operator*(double escalar) const;
    double dot(const Vetor& other) const;
    Vetor cross(const Vetor& other) const;
    double norm() const;
    Vetor normalize() const;
    
    // Operador de saída
    friend std::ostream& operator<<(std::ostream& os, const Vetor& v);
    
private:
    double x, y, z;
};

#endif // VETOR_H