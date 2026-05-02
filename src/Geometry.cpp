#include "Geometry.h"
#include <cmath>

double intersect_sphere(const Ponto& origem, const Vetor& direcao, 
                        const Ponto& centro, double raio) {
    // v = origem - centro
    Vetor v = origem - centro;
    
    double v_dot_d = v.dot(direcao);
    double v_dot_v = v.dot(v);
    double r2 = raio * raio;
    
    double discriminant = (v_dot_d * v_dot_d) - (v_dot_v - r2);
    
    if (discriminant < 0) {
        return INF;
    }
    
    double sqrt_disc = std::sqrt(discriminant);
    
    double t1 = -v_dot_d - sqrt_disc;
    double t2 = -v_dot_d + sqrt_disc;
    
    if (t1 > 0.001) return t1;
    if (t2 > 0.001) return t2;
    
    return INF;
}

double intersect_plane(const Ponto& origem, const Vetor& direcao, 
                       const Ponto& p0, const Vetor& normal) {
    double denom = direcao.dot(normal);
    
    if (std::abs(denom) > 1e-6) {
        Vetor p0_origem = p0 - origem;
        double t = p0_origem.dot(normal) / denom;
        
        if (t > 0.001) {
            return t;
        }
    }
    
    return INF;
}

double intersect_triangle(const Ponto& origem, const Vetor& direcao,
                          const Ponto& v0, const Ponto& v1, const Ponto& v2) {
    const double EPSILON = 1e-8;
    
    // Arestas do triângulo
    Vetor aresta1 = v1 - v0;
    Vetor aresta2 = v2 - v0;
    
    // Vetor perpendicular ao plano formado pela direção e aresta2
    Vetor h = direcao.cross(aresta2);
    double a = aresta1.dot(h);
    
    if (std::abs(a) < EPSILON) {
        return INF;  // Raio paralelo ao triângulo
    }
    
    double f = 1.0 / a;
    Vetor s = origem - v0;
    double u = f * s.dot(h);
    
    if (u < 0.0 || u > 1.0) {
        return INF;
    }
    
    Vetor q = s.cross(aresta1);
    double v = f * direcao.dot(q);
    
    if (v < 0.0 || (u + v) > 1.0) {
        return INF;
    }
    
    double t = f * aresta2.dot(q);
    
    if (t > 0.001) {
        return t;
    }
    
    return INF;
}

double intersect_triangles(const Ponto& origem, const Vetor& direcao,
                           const std::vector<Triangulo>& triangulos) {
    double min_t = INF;
    
    for (const auto& tri : triangulos) {
        double t = intersect_triangle(origem, direcao, tri.v0, tri.v1, tri.v2);
        if (t < min_t) {
            min_t = t;
        }
    }
    
    return min_t;
}