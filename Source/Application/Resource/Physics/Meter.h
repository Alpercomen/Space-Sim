#pragma once

#include <Application/Constants/Constants.h>

class Meter {
public:
	// Getters
	double GetWorld() { return world; }
	double GetNormal() { return normalized; }

	// Setters
	void SetWorld(double meter)
	{
		world = meter;
		normalized = meter / METERS_PER_UNIT;
	}

	void SetNormal(double meter)
	{
		world = meter * METERS_PER_UNIT;
		normalized = meter;
	}

private:
	float world;
	float normalized;
};