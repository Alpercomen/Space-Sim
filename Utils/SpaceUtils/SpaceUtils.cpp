#include "SpaceUtils.h"
#include "Constants.h"

double GravitationalForce(double mu, double r) {
	return mu / (r * r);
}