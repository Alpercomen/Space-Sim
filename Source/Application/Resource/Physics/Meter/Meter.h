#pragma once

#include <Application/Constants/Constants.h>

class Meter {
public:
	// Getters
	double get(bool normal = false) { return normal ? normalized : world; }

	// Setters
	void set(double meter, bool normal = false)
	{
		if (normal)
		{
			world = meter * METERS_PER_UNIT;
			normalized = meter;
		}
		else 
		{
			world = meter;
			normalized = meter / METERS_PER_UNIT;
		}
	}

private:
	float world;
	float normalized;
};