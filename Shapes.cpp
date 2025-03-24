#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shapes.h"
#include "Core.h"

#include <vector>

GLuint Shapes::CreateCircle(float centerX, float centerY, float radius, int res)
{
    std::vector<float> vertices;

    vertices.push_back(centerX);
    vertices.push_back(centerY);

    for (int i = 0; i <= res; ++i)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        vertices.push_back(x);
        vertices.push_back(y);
    }

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // For good practice
    return VAO;
}