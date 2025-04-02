#pragma once

#include "Position.h"
#include "Velocity.h"
#include "Acceleration.h"
#include "Meter.h"

// Stores the attributes of a circle
struct CircleDesc {
public:
	Position pos;
	Velocity vel;
	Acceleration acc;

	Meter radius;
	int res;
};

class Circle {
public:
	CircleDesc circleDesc;

	Circle() : circleDesc(CircleDesc()) {}
	Circle(CircleDesc& circleDesc) : circleDesc(circleDesc) {}

	void Accelerate(Acceleration& acceleration);
	void UpdatePos();
	void Draw();
};


GLuint CreateCircleVAO(CircleDesc& circleDesc);

