#include <iostream>
#include <GL/glew.h>

#include "Circle.h"
#include "Constants.h"

#include <vector>

GLuint CreateCircle(CircleDesc& circleDesc)
{
    std::vector<float> vertices;

    vertices.push_back(circleDesc.posX);
    vertices.push_back(circleDesc.posY);

    for (int i = 0; i <= circleDesc.res; ++i)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / circleDesc.res);
        float x = circleDesc.posX + cos(angle) * circleDesc.radius;
        float y = circleDesc.posY + sin(angle) * circleDesc.radius;
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