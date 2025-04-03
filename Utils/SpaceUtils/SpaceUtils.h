#pragma once

#include "vector"

#include "Circle.h"
#include "Vector.h"

double GravitationalForce(double mu, double r);

void Attract(Circle& obj, std::vector<Circle>& objects);