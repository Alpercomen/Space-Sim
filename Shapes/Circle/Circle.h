#pragma once

#include <GL/glew.h>

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
	int res = 50;

	double mass = 1.0;
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

