#ifndef PONTO_H
#define PONTO_H

#include <iostream>
#include <cmath>
#include "Vetor.h"

class Vetor;  // Declaração antecipada para resolver dependência circular

class Ponto {
public:
    // Construtor com valores padrão (equivalente ao __init__ do Python)
    Ponto(double x = 0.0, double y = 0.0, double z = 0.0);
    
    // Getters (equivalentes às properties do Python)
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    // Setters (opcionais, para modificar o ponto)
    void setX(double val) { x = val; }
    void setY(double val) { y = val; }
    void setZ(double val) { z = val; }
    
    // Ponto + Vetor = Ponto (Deslocamento)
    // Equivalente ao __add__ do Python
    Ponto operator+(const Vetor& other) const;
    
    // Ponto - Ponto = Vetor (Direção/distância entre eles)
    // Ponto - Vetor = Ponto (Recuar a posição)
    // Equivalente ao __sub__ do Python
    Vetor operator-(const Ponto& other) const;  // Ponto - Ponto
    Ponto operator-(const Vetor& other) const;   // Ponto - Vetor
    
    // Operador de saída (equivalente ao __repr__)
    friend std::ostream& operator<<(std::ostream& os, const Ponto& p);
    
    // Acesso estilo array (opcional, para compatibilidade com numpy)
    double operator[](int index) const;
    
private:
    double x, y, z;  // Equivalente ao _data do Python
};

#endif // PONTO_H