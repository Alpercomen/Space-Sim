#pragma once
#include <iostream>
#include <vector>

#include <Application/Resource/Mesh/Sphere/Sphere.h>
#include <Application/Core/Core.h>
#include <Application/Core/Engine/Engine.h>


Sphere::Sphere() : Sphere(SphereDesc()) {}
Sphere::Sphere(const SphereDesc& circleDesc) : m_circleDesc(circleDesc)
{
    m_circleDesc = circleDesc;
    m_sphereMesh = CreateSphereVAO(m_circleDesc);
}

Sphere::~Sphere()
{
    // Will get moved to a SceneManager, where it will handle the lifetime of a Sphere.
    // glDeleteVertexArrays(1, &m_sphereMesh.circleVAO);
}

SphereMesh Sphere::CreateSphereVAO(const SphereDesc& circleDesc)
{
    const unsigned int X_SEGMENTS = 50;
    const unsigned int Y_SEGMENTS = 50;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = cos(xSegment * 2.0f * Math::Pi) * sin(ySegment * Math::Pi);
            float yPos = cos(ySegment * Math::Pi);
            float zPos = sin(xSegment * 2.0f * Math::Pi) * sin(ySegment * Math::Pi);

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