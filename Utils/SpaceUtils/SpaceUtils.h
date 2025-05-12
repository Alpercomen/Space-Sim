#pragma once

#include "vector"
#include "Sphere/Sphere.h"

double GravitationalForce(double mu, double r);

double CalculateOrbitalVelocity(double otherMass, double r);

void Attract(Sphere& obj, std::vector<Sphere>& objects);

void PlaceInOrbit(SphereDesc& centerDesc, SphereDesc& orbittingDesc);

void InitializeSun(SphereDesc& sunDesc);

void InitializeEarth(SphereDesc& earthDesc);

void InitializeMoon(SphereDesc& moonDesc);

void SetSolarSystem(std::vector<Sphere>& objects);