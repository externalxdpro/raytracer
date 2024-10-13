#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>
#include <format>
#include <iostream>

class Vec3 {
  public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    const Vec3 operator-() { return Vec3(-x, -y, -z); }

    Vec3 &operator+=(const Vec3 &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3 &operator*=(double t) {
        this->x *= t;
        this->y *= t;
        this->z *= t;
        return *this;
    }

    Vec3 &operator/=(double t) { return *this *= 1 / t; }

    const double length() { return std::sqrt(length_squared()); }
    const double length_squared() { return x * x + y * y + z * z; }

    std::ostream &operator<<(std::ostream &out) {
        return out << std::format("{} {} {}", this->x, this->y, this->z);
    }

    Vec3 operator+(const Vec3 &other) {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    Vec3 operator-(const Vec3 &other) {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Vec3 operator*(const Vec3 &other) {
        return {this->x * other.x, this->y * other.y, this->z * other.z};
    }
    Vec3 operator*(double t) { return {t * this->x, t * this->y, t * this->z}; }

    Vec3 operator/(double t) { return *this * (1 / t); }

    double dot(const Vec3 &other) {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vec3 cross(const Vec3 &other) {
        return {this->y * other.z - this->z * other.y,
                this->z * other.x - this->x * other.z,
                this->x * other.y - this->y * other.x};
    }

    Vec3 unitVector() { return *this / this->length(); }
};

#endif // VEC3_H_
