#pragma once
#include <iostream>

#include <Application/Resource/Entities/Sphere/Sphere.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Engine/Engine.h>

#include <vector>

Sphere::Sphere() : Sphere(SphereDesc()) {}
Sphere::Sphere(const SphereDesc& circleDesc) : circleDesc(circleDesc)
{
    sphereMesh = CreateSphereVAO(circleDesc);
}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &sphereMesh.circleVAO);
}

SphereMesh Sphere::CreateSphereVAO(const SphereDesc& circleDesc)
{
    const unsigned int X_SEGMENTS = 50;
    const unsigned int Y_SEGMENTS = 50;
    const float PI = 3.14159265359f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI);
            float yPos = cos(ySegment * PI);
            float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI);

            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    SphereMesh mesh;
    mesh.circleVAO = VAO;
    mesh.indexCount = static_cast<GLuint>(indices.size());
    return mesh;
}

void Sphere::Accelerate(Acceleration& acceleration)
{
    // Update acceleration
    circleDesc.acc = acceleration;

    // Physics update in meters
    circleDesc.vel.setY(circleDesc.vel.getY() + circleDesc.acc.getY() * DELTA_TIME * TIME_SCALE);
    circleDesc.vel.setX(circleDesc.vel.getX() + circleDesc.acc.getX() * DELTA_TIME * TIME_SCALE);
    circleDesc.vel.setZ(circleDesc.vel.getZ() + circleDesc.acc.getZ() * DELTA_TIME * TIME_SCALE);
}

void Sphere::UpdatePos()
{
    double nextX = circleDesc.pos.getX() + circleDesc.vel.getX() * DELTA_TIME * TIME_SCALE;
    circleDesc.pos.setX(nextX);

    double nextY = circleDesc.pos.getY() + circleDesc.vel.getY() * DELTA_TIME * TIME_SCALE;
    circleDesc.pos.setY(nextY);

    double nextZ = circleDesc.pos.getZ() + circleDesc.vel.getZ() * DELTA_TIME * TIME_SCALE;
    circleDesc.pos.setZ(nextZ);
}

void Sphere::Draw(Camera& camera, GLuint shader, float aspectRatio)
{
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 1e25f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, circleDesc.pos.getPosition());

    float scaledRadius = circleDesc.radius.get(true) * METERS_PER_UNIT;
    model = glm::scale(model, glm::vec3(scaledRadius));

    glm::mat4 mvp = projection * view * model;
    GLuint mvpLoc = glGetUniformLocation(shader, "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    GLuint topColorLoc = glGetUniformLocation(shader, "topColor");
    glUniform3fv(topColorLoc, 1, glm::value_ptr(this->circleDesc.topColor));

    GLuint botColorLoc = glGetUniformLocation(shader, "botColor");
    glUniform3fv(botColorLoc, 1, glm::value_ptr(this->circleDesc.botColor));

    glBindVertexArray(sphereMesh.circleVAO);
    glDrawElements(GL_TRIANGLE_STRIP, sphereMesh.indexCount, GL_UNSIGNED_INT, 0);
}