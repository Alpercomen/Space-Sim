#pragma once

#include <vector>
#include <Application/Resource/Mesh/Sphere/Sphere.h>
#include <Application/Core/Core.h>

double GravitationalForce(double mu, double r);

double CalculateOrbitalVelocity(double otherMass, double r);

void InitializeCircularOrbit(EntityID satelliteID, EntityID attractorID);

void Attract(EntityID& objID);