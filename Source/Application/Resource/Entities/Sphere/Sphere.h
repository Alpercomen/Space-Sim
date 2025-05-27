#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application/Resource/Components/Transform/Position/Position.h>
#include <Application/Resource/Physics/Velocity/Velocity.h>
#include <Application/Resource/Physics/Acceleration/Acceleration.h>
#include <Application/Resource/Physics/Meter/Meter.h>
#include <Application/Resource/Entities/Camera/Camera.h>

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


class Sphere {
public:
	SphereDesc circleDesc;
	SphereMesh sphereMesh;

	Sphere();
	Sphere(const SphereDesc& circleDesc);

	~Sphere();

	SphereMesh CreateSphereVAO(const SphereDesc& circleDesc);
	void Accelerate(Acceleration& acceleration);
	void UpdatePos();
	void Draw(Camera& camera, GLuint shader, float aspectRatio);
};



