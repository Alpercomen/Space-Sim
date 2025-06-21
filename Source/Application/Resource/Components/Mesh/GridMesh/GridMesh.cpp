#pragma once
#include "GridMesh.h"

GridMesh::GridMesh(int width, int height, float spacing)
    : width(width), height(height), spacing(spacing) 
{

    float halfWidth = width * spacing * 0.5f;
    float halfHeight = height * spacing * 0.5f;

    // Generate vertical lines (parallel to Z axis)
    for (int x = 0; x <= width; ++x) {
        float xPos = x * spacing - halfWidth;
        vertices.emplace_back(xPos, 0.0f, -halfHeight); // bottom
        vertices.emplace_back(xPos, 0.0f, halfHeight); // top
    }

    // Generate horizontal lines (parallel to X axis)
    for (int z = 0; z <= height; ++z) {
        float zPos = z * spacing - halfHeight;
        vertices.emplace_back(-halfWidth, 0.0f, zPos); // left
        vertices.emplace_back(halfWidth, 0.0f, zPos); // right
    }

    // No index buffer needed — just draw with glDrawArrays

    shader = Shader(
        R"(D:\Documents\Projects\Nyx\Source\Application\Shaders\Grid\grid.vert)",
        R"(D:\Documents\Projects\Nyx\Source\Application\Shaders\Grid\grid.frag)"
    );
}

void GridMesh::UploadToGPU() 
{
    glGenVertexArrays(1, &mesh.vao.m_data);
    glGenBuffers(1, &mesh.vbo.m_data);

    glBindVertexArray(mesh.vao.m_data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo.m_data);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void GridMesh::Draw(const Math::Mat4f& mvp) const 
{
    shader.Use();

    GLuint mvpLoc = glGetUniformLocation(shader.GetID(), "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(mesh.vao.m_data);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);
}

void GridMesh::BendVertices(float time) 
{
    for (int z = 0; z <= height; ++z) 
    {
        for (int x = 0; x <= width; ++x) 
        {
            int i = z * (width + 1) + x;
            glm::vec3& v = vertices[i];

            float dx = v.x - (width * spacing / 2.0f);
            float dz = v.z - (height * spacing / 2.0f);
            float dist = sqrt(dx * dx + dz * dz);

            // Simulated gravitational wave / curvature effect
            float curvature = sin(dist * 0.2f - time * 2.0f) * exp(-dist * 0.1f);

            v.y = curvature * 3.0f; // amplify the effect
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo.m_data);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), vertices.data());
}