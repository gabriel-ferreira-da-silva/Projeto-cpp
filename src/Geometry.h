#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Ponto.h"
#include "Vetor.h"
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

const double INF = std::numeric_limits<double>::infinity();
const double EPSILON = 1e-8;

/**
 * Calcula a interseção entre um raio e uma esfera.
 * Retorna a distância t do ponto de interseção ou INF se não houver.
 */
double intersect_sphere(const Ponto& origem, const Vetor& direcao, 
                        const Ponto& centro, double raio);

/**
 * Calcula a interseção entre um raio e um plano.
 * Retorna a distância t do ponto de interseção ou INF se não houver.
 */
double intersect_plane(const Ponto& origem, const Vetor& direcao, 
                       const Ponto& p0, const Vetor& normal);

/**
 * Estrutura para armazenar um triângulo (3 vértices)
 */
struct Triangulo {
    Ponto v0, v1, v2;
    
    Triangulo(const Ponto& v0, const Ponto& v1, const Ponto& v2)
        : v0(v0), v1(v1), v2(v2) {}
};

/**
 * Interseção raio-triângulo usando o algoritmo Möller–Trumbore.
 * Testa um único triângulo.
 * Retorna a distância t ou INF se não houver interseção.
 */
double intersect_triangle(const Ponto& origem, const Vetor& direcao,
                          const Ponto& v0, const Ponto& v1, const Ponto& v2);

/**
 * Interseção raio-triângulo para múltiplos triângulos.
 * Versão vetorizada (sem dependência do NumPy).
 * Retorna o menor t válido ou INF se não houver interseção.
 */
double intersect_triangles(const Ponto& origem, const Vetor& direcao,
                           const std::vector<Triangulo>& triangulos);

#endif // INTERSECT_H