#pragma once

// Stores the attributes of a circle
struct CircleDesc {
	float posX;
	float posY;
	float velX;
	float velY;
	float radius;
	int res;
};


GLuint CreateCircle(CircleDesc& circleDesc);

