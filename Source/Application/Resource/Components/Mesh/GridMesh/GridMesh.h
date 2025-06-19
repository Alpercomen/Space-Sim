#pragma once

#include <Application/Resource/Components/Mesh/Mesh.h>

class GridMesh {
public:
    GridMesh(int width, int height, float spacing);

    void UploadToGPU();
    void Render() const;

    void BendVertices(float time); // for spacetime curvature animation

private:
    Vector<Math::Vec3f> vertices;
    Vector<uint32> indices;

    Mesh mesh;
    int width, height;
    float spacing;
};