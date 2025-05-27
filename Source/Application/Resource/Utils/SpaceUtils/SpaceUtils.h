#pragma once

#include <vector>
#include <Application/Resource/Entities/Sphere/Sphere.h>
#include <Application/Core/Core.h>

double GravitationalForce(double mu, double r);

double CalculateOrbitalVelocity(double otherMass, double r);

void Attract(SharedPtr<Sphere>& obj, Vector<SharedPtr<Sphere>>& objects);

Vector<SharedPtr<Sphere>> CreateSolarSystem();