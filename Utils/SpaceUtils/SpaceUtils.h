#pragma once

#include "vector"

#include "Sphere/Sphere.h"

double GravitationalForce(double mu, double r);

double CalculateOrbitalVelocity(double otherMass, double r);

void Attract(Sphere& obj, std::vector<Sphere>& objects);