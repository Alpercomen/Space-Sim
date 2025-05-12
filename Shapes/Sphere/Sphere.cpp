#include <iostream>


#include "Sphere.h"
#include "Constants.h"

#include <vector>

SphereMesh CreateSphereVAO(SphereDesc& circleDesc)
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
    circleDesc.setAcceleration(acceleration.getAcceleration());

    // Physics update in meters
    glm::vec3 velocity = circleDesc.getVelocity();
    double nextX = (velocity.x + acceleration.getX()) * DELTA_TIME * TIME_SCALE;
    double nextY = (velocity.y + acceleration.getY()) * DELTA_TIME * TIME_SCALE;
    double nextZ = (velocity.z + acceleration.getZ()) * DELTA_TIME * TIME_SCALE;

    circleDesc.setVelocity(glm::vec3(nextX, nextY, nextZ));

}

void Sphere::UpdatePos()
{
    Position position = circleDesc.getPosition();
    Velocity velocity = circleDesc.getVelocity();

    double nextX = position.getX() + velocity.getX() * DELTA_TIME * TIME_SCALE;
    double nextY = position.getY() + velocity.getY() * DELTA_TIME * TIME_SCALE;
    double nextZ = position.getZ() + velocity.getZ() * DELTA_TIME * TIME_SCALE;

    circleDesc.setPosition(glm::vec3(nextX, nextY, nextZ));
}

void Sphere::Draw(Camera& camera, double aspectRatio, GLuint shader)
{
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)aspectRatio, 0.1f, 1e25f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, circleDesc.getPosition());

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