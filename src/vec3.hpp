#ifndef VEC3_H_
#define VEC3_H_

#include "util.hpp"

#include <cmath>
#include <format>
#include <iostream>

class Vec3 {
  public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

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

    const double length() const { return std::sqrt(this->lengthSquared()); }
    const double lengthSquared() const {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    bool nearZero() const {
        double s = 1e-8;
        return std::fabs(this->x) < s && std::fabs(this->y) < s &&
               std::fabs(this->z) < s;
    }

    static Vec3 rand() { return {randDouble(), randDouble(), randDouble()}; }

    static Vec3 rand(double min, double max) {
        return {randDouble(min, max), randDouble(min, max),
                randDouble(min, max)};
    }

    std::ostream &operator<<(std::ostream &out) const {
        return out << std::format("{} {} {}", this->x, this->y, this->z);
    }

    Vec3 operator+(const Vec3 &other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    Vec3 operator-(const Vec3 &other) const {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Vec3 operator*(const Vec3 &other) const {
        return {this->x * other.x, this->y * other.y, this->z * other.z};
    }
    Vec3 operator*(double t) const {
        return {t * this->x, t * this->y, t * this->z};
    }

    Vec3 operator/(double t) const { return *this * (1 / t); }

    double dot(const Vec3 &other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vec3 cross(const Vec3 &other) const {
        return {this->y * other.z - this->z * other.y,
                this->z * other.x - this->x * other.z,
                this->x * other.y - this->y * other.x};
    }

    Vec3 unitVector() const { return *this / this->length(); }

    static Vec3 randUnitVector() {
        while (true) {
            Vec3   p     = Vec3::rand(-1, 1);
            double lensq = p.lengthSquared();
            if (1e-160 < lensq && lensq <= 1) {
                return p / sqrt(lensq);
            }
        }
    }

    Vec3 randOnHemisphere() const {
        Vec3 onUnitSphere = randUnitVector();
        if (this->dot(onUnitSphere) > 0.0) {
            return onUnitSphere;
        }
        return -onUnitSphere;
    }

    Vec3 reflect(const Vec3 &n) const { return *this - n * this->dot(n) * 2; }
};

#endif // VEC3_H_
