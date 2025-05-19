#pragma once

#include <vector>
#include <Application/Shapes/Sphere/Sphere.h>

double GravitationalForce(double mu, double r);

double CalculateOrbitalVelocity(double otherMass, double r);

void Attract(std::shared_ptr<Sphere>& obj, std::vector<std::shared_ptr<Sphere>>& objects);

std::vector<std::shared_ptr<Sphere>> CreateSolarSystem();