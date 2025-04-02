#include <iostream>
#include <GL/glew.h>

#include "Circle.h"
#include "Constants.h"

#include <vector>

GLuint CreateCircleVAO(CircleDesc& circleDesc)
{
    std::vector<float> vertices;

    vertices.push_back(circleDesc.pos.getX(true));
    vertices.push_back(circleDesc.pos.getY(true));

    for (int i = 0; i <= circleDesc.res; ++i)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / circleDesc.res);
        float x = circleDesc.pos.getX(true) + cos(angle) * circleDesc.radius.get(true);
        float y = circleDesc.pos.getY(true) + sin(angle) * circleDesc.radius.get(true);
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

void Circle::Accelerate(Acceleration& acceleration)
{
    // Update acceleration
    circleDesc.acc = acceleration;

    // Physics update in meters
    circleDesc.vel.setY(circleDesc.vel.getY() + circleDesc.acc.getY() * DELTA_TIME);
    circleDesc.vel.setX(circleDesc.vel.getX() + circleDesc.acc.getX() * DELTA_TIME);
    circleDesc.vel.setZ(circleDesc.vel.getZ() + circleDesc.acc.getZ() * DELTA_TIME);
}

void Circle::UpdatePos()
{
    // Y Axis Collision check
    double nextY = circleDesc.pos.getY() + circleDesc.vel.getY() * DELTA_TIME;

    if (nextY - circleDesc.radius.get() <= -METERS_PER_UNIT) {
        // Mirror position relative to wall
        double overshoot = -METERS_PER_UNIT - (nextY - circleDesc.radius.get());
        circleDesc.pos.setY(-METERS_PER_UNIT + circleDesc.radius.get() + overshoot);
        circleDesc.vel.setY(std::abs(circleDesc.vel.getY()));  // Going upward
    }
    else if (nextY + circleDesc.radius.get() >= METERS_PER_UNIT) {
        double overshoot = (nextY + circleDesc.radius.get()) - METERS_PER_UNIT;
        circleDesc.pos.setY(METERS_PER_UNIT - circleDesc.radius.get() - overshoot);
        circleDesc.vel.setY(-std::abs(circleDesc.vel.getY()));  // Going downward
    }
    else {
        circleDesc.pos.setY(nextY);
    }

    // X axis collision check
    double nextX = circleDesc.pos.getX() + circleDesc.vel.getX() * DELTA_TIME;

    if (nextX - circleDesc.radius.get() <= -METERS_PER_UNIT) {
        // Mirror position relative to wall
        double overshoot = -METERS_PER_UNIT - (nextY - circleDesc.radius.get());
        circleDesc.pos.setX(-METERS_PER_UNIT + circleDesc.radius.get() + overshoot);
        circleDesc.vel.setX(std::abs(circleDesc.vel.getX()));  // Going upward
    }
    else if (nextX + circleDesc.radius.get() >= METERS_PER_UNIT) {
        double overshoot = (nextX + circleDesc.radius.get()) - METERS_PER_UNIT;
        circleDesc.pos.setX(METERS_PER_UNIT - circleDesc.radius.get() - overshoot);
        circleDesc.vel.setX(-std::abs(circleDesc.vel.getX()));  // Going downward
    }
    else {
        circleDesc.pos.setX(nextX);
    }
}

void Circle::Draw()
{
    // Use core pipeline
    GLuint circleVAO = CreateCircleVAO(circleDesc);
    glBindVertexArray(circleVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, circleDesc.res + 2);
}