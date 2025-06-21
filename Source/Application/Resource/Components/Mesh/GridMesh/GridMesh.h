#pragma once

#include <Application/Core/Core.h>
#include <Application/Resource/Components/Mesh/Mesh.h>

class GridMesh {
public:
    GridMesh(int width, int height, float spacing);

    void UploadToGPU();
    void Draw(const Math::Mat4f& mvp) const;

    void BendVertices(float time); // for spacetime curvature animation

private:
    Vector<Math::Vec3f> vertices;
    Vector<uint32> indices;

    Mesh mesh;
    Shader shader;
    int width, height;
    float spacing;
};
