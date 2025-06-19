#pragma once
#include "GridMesh.h"

GridMesh::GridMesh(int width, int height, float spacing)
    : width(width), height(height), spacing(spacing) {

    for (int z = 0; z <= height; ++z) {
        for (int x = 0; x <= width; ++x) {
            vertices.emplace_back(x * spacing, 0.0f, z * spacing);
        }
    }

    for (int z = 0; z < height; ++z) {
        for (int x = 0; x < width; ++x) {
            int start = z * (width + 1) + x;

            indices.push_back(start);
            indices.push_back(start + 1);
            indices.push_back(start + width + 1);

            indices.push_back(start + 1);
            indices.push_back(start + width + 2);
            indices.push_back(start + width + 1);
        }
    }
}

void GridMesh::UploadToGPU() {
    glGenVertexArrays(1, &mesh.vao.m_data);
    glGenBuffers(1, &mesh.vbo.m_data);
    glGenBuffers(1, &mesh.ebo.m_data);

    glBindVertexArray(mesh.vao.m_data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo.m_data);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo.m_data);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void GridMesh::Render() const {
    glBindVertexArray(mesh.vao.m_data);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GridMesh::BendVertices(float time) {
    for (int z = 0; z <= height; ++z) {
        for (int x = 0; x <= width; ++x) {
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