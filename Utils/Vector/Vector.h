#pragma once

#include <cmath>
#include <iostream>

class Vector
{
public:
	double x;
	double y;
	double z;

	Vector() : x(0.0), y(0.0), z(0.0) {}
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	double magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector normal() const {
		double mag = magnitude();
		if (mag == 0.0)
			return Vector(0.0, 0.0, 0.0);

		return Vector(x / mag, y / mag, z / mag);
	}

    // Rotation around axes (right-handed system)
    void rotate_x(double angle_rad) {
        y = y * std::cos(angle_rad) - z * std::sin(angle_rad);
        z = y * std::sin(angle_rad) + z * std::cos(angle_rad);
    }

    void rotate_y(double angle_rad) {
        x = x * std::cos(angle_rad) + z * std::sin(angle_rad);
        z = -x * std::sin(angle_rad) + z * std::cos(angle_rad);
    }

    void rotate_z(double angle_rad) {
        x = x * std::cos(angle_rad) - y * std::sin(angle_rad);
        y = x * std::sin(angle_rad) + y * std::cos(angle_rad);
    }

    // Dot product
    double dot(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector cross(const Vector& other) const {
        return Vector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Operator overloads
    Vector operator+(const Vector& rhs) const {
        return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector operator-(const Vector& rhs) const {
        return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector operator*(double scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator/(double scalar) const {
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    void print() const {
        std::cout << "Vec3(" << x << ", " << y << ", " << z << ")\n";
    }
};

