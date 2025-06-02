#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Application/Resource/Components/Transform/Position.h>
#include <Application/Resource/Physics/Velocity.h>
#include <Application/Resource/Physics/Acceleration.h>
#include <Application/Resource/Physics/Meter.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/EntityManager/EntityManager.h>

namespace SpaceSim
{
    struct SphereMesh
    {
        GLuint circleVAO;
        GLuint indexCount;
    };

    // Stores the attributes of a circle
    struct SphereDesc {
    public:
        Meter radius;
        int32 res = 50;

        Math::Vec3f topColor;
        Math::Vec3f botColor;
    };


    class Sphere {
    public:
        SphereDesc m_circleDesc;
        SphereMesh m_sphereMesh;

        Sphere() : Sphere(SphereDesc()) {}
        Sphere(const SphereDesc& circleDesc) : m_circleDesc(circleDesc)
        {
            m_circleDesc = circleDesc;
            m_sphereMesh = CreateSphereMesh(m_circleDesc);
        }

        ~Sphere()
        {
            // Will get moved to a SceneManager, where it will handle the lifetime of a Sphere.
            // glDeleteVertexArrays(1, &m_sphereMesh.circleVAO);
        }

        SphereMesh CreateSphereMesh(const SphereDesc& circleDesc)
        {
            const uint32 X_SEGMENTS = circleDesc.res;
            const uint32 Y_SEGMENTS = circleDesc.res;

            Vector<float> vertices;
            Vector<unsigned int> indices;

            for (uint32 y = 0; y <= Y_SEGMENTS; ++y)
            {
                for (uint32 x = 0; x <= X_SEGMENTS; ++x)
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
            for (uint32 y = 0; y < Y_SEGMENTS; ++y)
            {
                if (!oddRow)
                {
                    for (uint32 x = 0; x <= X_SEGMENTS; ++x)
                    {
                        indices.push_back(y * (X_SEGMENTS + 1) + x);
                        indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    }
                }
                else
                {
                    for (int32 x = X_SEGMENTS; x >= 0; --x)
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
    };
}



