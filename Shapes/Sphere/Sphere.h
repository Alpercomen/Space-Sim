#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Position/Position.h"
#include "Velocity/Velocity.h"
#include "Acceleration/Acceleration.h"
#include "Meter/Meter.h"

#include "Camera/Camera.h"

struct SphereMesh 
{
	GLuint circleVAO;
	GLuint indexCount;
};

// Stores the attributes of a circle
struct SphereDesc {
public:
	std::string name = "NO_NAME";

	Position pos;
	Velocity vel;
	Acceleration acc;

	Meter radius;
	int res = 50;

	double mass = 1.0;

	glm::vec3 topColor;
	glm::vec3 botColor;
};

SphereMesh CreateSphereVAO(SphereDesc& circleDesc);

class Sphere {
public:
	SphereDesc circleDesc;
	SphereMesh sphereMesh;

	Sphere() : circleDesc(SphereDesc()) 
	{
		sphereMesh = CreateSphereVAO(circleDesc);
	}
	Sphere(SphereDesc& circleDesc) : circleDesc(circleDesc) 
	{
		sphereMesh = CreateSphereVAO(circleDesc);
	}

	~Sphere()
	{
		glDeleteVertexArrays(1, &sphereMesh.circleVAO);
	}

	void Accelerate(Acceleration& acceleration);
	void UpdatePos();
	void Draw(Camera& camera, GLuint shader, float aspectRatio);
};



