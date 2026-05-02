#include "Vetor.h"

Vetor::Vetor(double x, double y, double z) : x(x), y(y), z(z) {}

Vetor Vetor::operator+(const Vetor& other) const {
    return Vetor(x + other.x, y + other.y, z + other.z);
}

Vetor Vetor::operator-(const Vetor& other) const {
    return Vetor(x - other.x, y - other.y, z - other.z);
}

Vetor Vetor::operator*(double escalar) const {
    return Vetor(x * escalar, y * escalar, z * escalar);
}

double Vetor::dot(const Vetor& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vetor Vetor::cross(const Vetor& other) const {
    return Vetor(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

double Vetor::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vetor Vetor::normalize() const {
    double n = norm();
    if (n > 0) {
        return Vetor(x / n, y / n, z / n);
    }
    return Vetor(0, 0, 0);
}

std::ostream& operator<<(std::ostream& os, const Vetor& v) {
    os << "Vetor(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}