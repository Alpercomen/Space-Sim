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
	Meter radius;
	int res = 50;
	double mass = 1.0;

	glm::vec3 topColor;
	glm::vec3 botColor;

	glm::vec3 getPosition(bool normal = false) { return pos.getPosition(normal); }
	glm::vec3 getVelocity(bool normal = false) { return vel.getVelocity(normal); }
	glm::vec3 getAcceleration(bool normal = false) { return acc.getAcceleration(normal); }

	void setPosition(glm::vec3 pos, bool normal = false) { this->pos.setPosition(pos, normal); }
	void setVelocity(glm::vec3 vel, bool normal = false) { this->vel.setVelocity(vel, normal); }
	void setAcceleration(glm::vec3 acc, bool normal = false) { this->acc.setAcceleration(acc, normal); }

private:
	Position pos;
	Velocity vel;
	Acceleration acc;

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
	void Draw(Camera& camera, double aspectRatio, GLuint shader);
};



