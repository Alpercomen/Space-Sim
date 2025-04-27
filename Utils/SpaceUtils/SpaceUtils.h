#pragma once

#include "vector"

#include "Sphere/Sphere.h"
#include "Vector/Vector.h"

double GravitationalForce(double mu, double r);

void Attract(Sphere& obj, std::vector<Sphere>& objects);