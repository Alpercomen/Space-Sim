#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application/Resource/Transform/Position.h>
#include <Application/Resource/Physics/Velocity.h>
#include <Application/Resource/Physics/Acceleration.h>
#include <Application/Resource/Physics/Meter.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/EntityManager/EntityManager.h>

using namespace SpaceSim;

struct SphereMesh 
{
	GLuint circleVAO;
	GLuint indexCount;
};

// Stores the attributes of a circle
struct SphereDesc {
public:
	Meter radius;
	int res = 50;

	glm::vec3 topColor;
	glm::vec3 botColor;
};


class Sphere {
public:
	SphereDesc m_circleDesc;
	SphereMesh m_sphereMesh;

	Sphere();
	Sphere(const SphereDesc& circleDesc);

	~Sphere();

	SphereMesh CreateSphereVAO(const SphereDesc& circleDesc);
};



